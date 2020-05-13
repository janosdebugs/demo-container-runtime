
#include <mntent.h>
#include <sys/mount.h>
#include "MountNamespaceSeparationPlugin.h"

void MountNamespaceSeparationPlugin::beforeClone() noexcept(false) {

}

int MountNamespaceSeparationPlugin::getCloneFlags() {
    return 0;
}

void MountNamespaceSeparationPlugin::afterClone() noexcept(false) {
    struct mntent *mountEntry;
    FILE *procFile;

    procFile = setmntent("/proc/mounts", "r");
    if (procFile == nullptr) {
        perror("setmntent on /proc/mounts failed");
        exit(1);
    }
    while (nullptr != (mountEntry = getmntent(procFile))) {
        if (mount(nullptr, mountEntry->mnt_dir, mountEntry->mnt_type, MS_REC|MS_SLAVE, nullptr) < 0) {
            throw SeparationFailedException(std::string("Remount failed on ") + std::string(mountEntry->mnt_dir));
        }
    }
    endmntent(procFile);
}

MountNamespaceSeparationPlugin::~MountNamespaceSeparationPlugin() = default;
