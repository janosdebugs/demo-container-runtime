
#include <utility>
#include <vector>
#include <zconf.h>
#include <string>
#include <csignal>
#include <wait.h>
#include <memory>
#include <memory.h>
#include <iostream>
#include "plugin/SeparationPlugin.h"
#include "plugin/SeparationPluginList.h"

SeparationPluginList plugins; // NOLINT
std::vector<std::string> argv;
std::string image;

/**
 * This method encapsulates the C string magic.
 *
 * @param argv
 *
 * @return the response code from the executable.
 */
int execute(std::vector<std::string> argv) {
    auto cStringArgv = std::vector<const char *>();
    for (auto &argvItem : argv) {
        cStringArgv.push_back(argvItem.c_str());
    }

    char * cArgv[cStringArgv.size() + 1];
    for (int i = 0; i < cStringArgv.size(); i++) {
        cArgv[i] = strdup(cStringArgv[i]);
    }
    cArgv[cStringArgv.size()] = (char *)nullptr;

    if (execv(cArgv[0], cArgv) < 0) {
        throw SeparationFailedException("execve failed");
    }
}

/**
 * This method is run as a child within the separated environment. Since the clone API does not allow OOP semantics,
 * we have to work around that by using a global variable for argv and plugins. This is not ideal and should probably
 * have some sort of locking.
 *
 * @param ignored this parameter is ignored because it uses c-style semantics and is easy to f* up.
 * @return the response code from the executable.
 */
int child(void * ignored) {
    for (auto plugin : plugins.getPlugins()) {
        plugin->afterClone();
    }

    return execute(argv);
}

pid_t separate(int flags) throw(SeparationFailedException) {
    //region stack magic
    size_t STACK_SIZE = 1024 * 1024;
    void *stack = malloc(STACK_SIZE);
    if (stack == nullptr) {
        throw SeparationFailedException("Child stack allocation failed.");
    }
    //Yeah, this is a bad idea. Feel free to suggest something better.
    void *stackTop = stack + STACK_SIZE;
    //endregion

    pid_t childPid = clone(
        child,
        stackTop,
        flags,
        {}
    );
    if (childPid < 0) {
        throw SeparationFailedException("Clone failed. Are you root?");
    }
    return childPid;
}

int run_separated(const SeparationPluginList &pluginList, const std::vector<std::string> &argvList) throw(SeparationFailedException) {
    //Use global variable hack to avoid pointer magic
    plugins = pluginList;
    argv = argvList;

    int flags = CLONE_NEWNS | SIGCHLD;
    for (auto plugin : plugins.getPlugins()) {
        plugin->beforeClone();
        flags = flags | plugin->getCloneFlags();
    }

    pid_t childPid = separate(flags);

    int status;
    pid_t exitedPid;
    do {
        exitedPid = wait(&status);
    } while (exitedPid != childPid);
}
