/**************************************************************************************************/
/* ATTENTION! This program was written for demonstration purposes only! Do not use in production! */
/**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sched.h>
#include <wait.h>
#include <sys/mount.h>
#include <mntent.h>


static int child(void* arg) {
    //region Remount all mount points as slaves, so they can be unmounted independently.
    struct mntent *mountEntry;
    FILE *procFile;

    procFile = setmntent("/proc/mounts", "r");
    if (procFile == nullptr) {
        perror("setmntent on /proc/mounts failed");
        exit(1);
    }
    while (nullptr != (mountEntry = getmntent(procFile))) {
        printf("Remounting %s as slave...\n", mountEntry->mnt_dir);
        if (mount(nullptr, mountEntry->mnt_dir, mountEntry->mnt_type, MS_REC|MS_SLAVE, nullptr) < 0) {
            perror("Mount failed.");
            exit(EXIT_FAILURE);
        }
    }
    endmntent(procFile);
    //endregion

    //region start bash
    printf("Starting bash inside a mount namespace. You should be able to safely unmount any mount point...\n");
    char bashPath[] = "/bin/bash";
    char *const paramList[] = {bashPath};
    if (execv(bashPath, paramList) < 0) {
        perror("Failed running bash inside the container.");
        return -1;
    }
    //endregion
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


    pid_t childPid = clone(
            reinterpret_cast<int (*)(void *)>(child),
            stackTop,
            //Note: mount namespaces are implicitly added with CLONE_NEWNS.
            CLONE_NEWNS | SIGCHLD,
            {}
    );
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