#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <seccomp.h>
#include <fcntl.h>
#include <zconf.h>

int main(int argc, char **argv, char **envp) {
    int ret;
    scmp_filter_ctx ctx;

    ctx = seccomp_init(SCMP_ACT_ALLOW);
    if (ctx == nullptr) {
        printf("Failed initializing seccomp\n");
        exit(1);
    }
    ret = seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(bind), 0);
    if (ret < 0) {
        printf("Failed denying bind via seccomp\n");
        exit(1);
    }
    ret = seccomp_load(ctx);
    if (ret < 0) {
        printf("Failed loading seccomp\n");
        exit(1);
    }

    printf("Now running bash with the bind syscall disabled. Try running telnet google.com 80 !\n");
    char bashPath[] = "/bin/bash";
    char *const paramList[] = {bashPath};
    if (execv(bashPath, paramList) < 0) {
        perror("Failed running bash.");
        return -1;
    }
}