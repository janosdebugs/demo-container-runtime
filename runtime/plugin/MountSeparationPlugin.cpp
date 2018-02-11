
#include <mntent.h>
#include <sys/mount.h>
#include "MountSeparationPlugin.h"

void MountSeparationPlugin::beforeClone() throw(SeparationFailedException) {

}

int MountSeparationPlugin::getCloneFlags() {
    return 0;
}

void MountSeparationPlugin::afterClone() throw(SeparationFailedException) {
    struct mntent *mountEntry;
    FILE *procFile;

    procFile = setmntent("/proc/mounts", "r");
    if (procFile == nullptr) {
        perror("setmntent on /proc/mounts failed");
        exit(1);
    }
    while (nullptr != (mountEntry = getmntent(procFile))) {
        printf("Remounting %s as slave...\n", mountEntry->mnt_dir);
        if (mount(nullptr, mountEntry->mnt_dir, mountEntry->mnt_type, MS_SLAVE, nullptr) < 0) {
            throw SeparationFailedException(std::string("Remount failed on ") + std::string(mountEntry->mnt_dir));
        }
    }
    endmntent(procFile);
}
