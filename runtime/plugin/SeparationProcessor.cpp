#include "SeparationProcessor.h"

#include <utility>
#include <csignal>
#include <cstdlib>
#include <sched.h>
#include <wait.h>
#include <zconf.h>
#include <functional>

SeparationProcessor::SeparationProcessor(SeparationPlugin ** plugins) {
    this->plugins = plugins;
}

int child(void **argv) {
    auto instance = (SeparationProcessor *) (argv[0]);
    auto *const * realArgv = static_cast<char *const *>(argv[1]);
    
    int i = 0;
    SeparationPlugin ** plugins = instance->getPlugins();
    while (plugins[i] != nullptr) {
        plugins[i]->afterClone();
    }

    if (execv(realArgv[0], realArgv) < 0) {
        throw SeparationFailedException();
    }
}

void SeparationProcessor::separate(char *const argv[]) {
    int flags = CLONE_NEWNS | SIGCHLD;
    int i = 0;
    while (plugins[i] != nullptr) {
        flags = flags | plugins[i]->getCloneFlags();
    }

    //region stack magic
    size_t STACK_SIZE = 1024 * 1024;
    void *stack = malloc(STACK_SIZE);
    if (stack == nullptr) {
        throw SeparationFailedException();
    }
    void *stackTop = stack + STACK_SIZE;
    //endregion

    SeparationProcessor * self = this;
    pid_t childPid = clone(
        reinterpret_cast<int (*)(void *)>(child),
        stackTop,
        flags,
        {
            self
        }
    );
    if (childPid < 0) {
        throw SeparationFailedException();
    }

    int status;
    pid_t exitedPid;
    do {
        exitedPid = wait(&status);
    } while (exitedPid != childPid);
}

SeparationPlugin ** SeparationProcessor::getPlugins() {
    return plugins;
}
