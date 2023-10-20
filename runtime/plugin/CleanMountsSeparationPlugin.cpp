#include <mntent.h>
#include <sys/mount.h>
#include "CleanMountsSeparationPlugin.h"
#include <list>

void CleanMountsSeparationPlugin::beforeClone() throw (SeparationFailedException) {

}

int CleanMountsSeparationPlugin::getCloneFlags() {
    return 0;
}

void CleanMountsSeparationPlugin::afterClone() throw (SeparationFailedException) {
    struct mntent *mountEntry;
    FILE *procFile;

    procFile = setmntent("/proc/mounts", "r");
    if (procFile == nullptr) {
        perror("setmntent on /proc/mounts failed");
        exit(1);
    }
    auto mountEntryList = std::list<std::string>();
    while (nullptr != (mountEntry = getmntent(procFile))) {
        if (std::string(mountEntry->mnt_dir) == "/") {
            continue;
        }
        if (std::string(mountEntry->mnt_dir) == "/dev") {
            // If /dev is a mount point, keep it, we need it for later.
            continue;
        }
        mountEntryList.emplace_back(mountEntry->mnt_dir);
    }
    mountEntryList.sort();
    mountEntryList.reverse();

    for (auto const& mountEntryString : mountEntryList) {
        umount(mountEntryString.c_str());
    }

    endmntent(procFile);
}

CleanMountsSeparationPlugin::~CleanMountsSeparationPlugin() = default;