/**
 * This program demonstrates how network namespaces work.
 *
 * ATTENTION! This program was written for demonstration purposes only! Do not use in production!
 *
 * @see https://pasztor.at/blog/under-the-hood-of-docker
 *
 * @author Janos Pasztor
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sched.h>
#include <wait.h>
#include <sys/mount.h>
#include <sys/utsname.h>

static int child(void *arg) {
    char bashPath[] = "/bin/bash";
    char *const paramList[] = {bashPath, nullptr};

    //Launch bash
    printf("Launching bash inside a network namespace. ifconfig should not show any interfaces...\n");
    if (execv(bashPath, paramList) < 0) {
        perror("Failed running bash.");
        return -1;
    }

    return 0;
}

int main() {
    //region stack magic
    size_t STACK_SIZE = 1024 * 1024;
    void *stack = malloc(STACK_SIZE);
    if (stack == nullptr) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    void *stackTop = stack + STACK_SIZE;
    //endregion

    pid_t childPid = clone(child, stackTop, CLONE_NEWNS | CLONE_NEWNET | SIGCHLD, {});
    if (childPid < 0) {
        perror("Clone failed");
        return -1;
    }

    int status;
    pid_t exitedPid;
    do {
        exitedPid = wait(&status);
        printf("Child exited: %i\n", exitedPid);
    } while (exitedPid != childPid);
}