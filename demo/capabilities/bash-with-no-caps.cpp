#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cap-ng.h>
#include <grp.h>
#include <sys/prctl.h>

void error(const char * message) {
    perror(message);
    exit(-1);
}

int main() {
    capng_clear(CAPNG_SELECT_BOTH);
    if (capng_apply(CAPNG_SELECT_BOTH))
        error("Failed to apply capabilities");

    char bashPath[] = "/bin/bash";
    char *const paramList[] = {bashPath, nullptr};
    if (execv(paramList[0], paramList) != 0) {
        perror("Failed to execute bash.");
        exit(EXIT_FAILURE);
    }
}