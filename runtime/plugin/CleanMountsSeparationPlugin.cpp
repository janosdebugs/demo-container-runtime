#include <mntent.h>
#include <sys/mount.h>
#include "CleanMountsSeparationPlugin.h"

void CleanMountsSeparationPlugin::beforeClone() noexcept(false) {

}

int CleanMountsSeparationPlugin::getCloneFlags() {
    return 0;
}

void CleanMountsSeparationPlugin::afterClone() noexcept(false) {
    struct mntent *mountEntry;
    FILE *procFile;

    procFile = setmntent("/proc/mounts", "r");
    if (procFile == nullptr) {
        perror("setmntent on /proc/mounts failed");
        exit(1);
    }
    while (nullptr != (mountEntry = getmntent(procFile))) {
        if (std::string(mountEntry->mnt_dir) == "/") {
            continue;
        }
        umount(mountEntry->mnt_dir);
    }
    endmntent(procFile);
}

CleanMountsSeparationPlugin::~CleanMountsSeparationPlugin() = default;