/**************************************************************************************************/
/* ATTENTION! This program was written for demonstration purposes only! Do not use in production! */
/**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sched.h>
#include <wait.h>
#include <sys/mount.h>

static int child(void *arg) {
    char bashPath[] = "/bin/bash";
    char *const paramList[] = {bashPath};

    //Make mount point into a slave so "outside" processes are not affected.
    printf("Changing the /proc mountpoint to slave...\n");
    if (mount("none", "/proc", nullptr, MS_REC|MS_SLAVE, nullptr) < 0) {
        perror("Mount failed.");
        exit(EXIT_FAILURE);
    }
    //Remount proc so the namespace takes effect
    printf("Remounting /proc so PID namespaces take effect...\n");
    if (mount("proc", "/proc", "proc", 0, nullptr) < 0) {
        perror("Mount failed.");
        exit(EXIT_FAILURE);
    }


    //Launch bash
    printf("Launching bash in a PID namespace. ps auwfx should not show any processes outside the container.\n");
    if (execv(bashPath, paramList) < 0) {
        perror("Failed running bash.");
        return -1;
    }
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

    pid_t childPid = clone(child, stackTop, CLONE_NEWNS | CLONE_NEWPID | SIGCHLD, {});
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