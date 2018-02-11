#include <mntent.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <zconf.h>
#include <fcntl.h>
#include <linux/loop.h>
#include <iostream>
#include "MountImageSeparationPlugin.h"

MountImageSeparationPlugin::MountImageSeparationPlugin(const std::string &image) {
    this->image = image;
}

void MountImageSeparationPlugin::beforeClone() throw(SeparationFailedException) {

}

int MountImageSeparationPlugin::getCloneFlags() {
    return 0;
}

void MountImageSeparationPlugin::afterClone() throw(SeparationFailedException) {
    struct stat statInfo{};
    if (lstat("/tmp/containerimage", &statInfo) < 0) {
        if (mkdir("/tmp/containerimage", 0700) < 0) {
            throw SeparationFailedException("Failed to mkdir /tmp/containerimage");
        }
    }

    int loopControlFileDescriptor = open("/dev/loop-control", O_RDWR);
    if (loopControlFileDescriptor == -1) {
        throw SeparationFailedException("Failed to open loop control device at /dev/loop-control");
    }

    long loopDeviceNumber = ioctl(loopControlFileDescriptor, LOOP_CTL_GET_FREE);
    if (loopDeviceNumber == -1) {
        throw SeparationFailedException("Failed to get free loop device number from /dev/loop-control");
    }

    char loopName[4096];
    sprintf(loopName, "/dev/loop%ld", loopDeviceNumber);

    auto loopFileDescriptor = open(loopName, O_RDWR);
    if (loopFileDescriptor == -1) {
        throw SeparationFailedException("Failed to open loop device at " + std::string(loopName));
    }

    auto backingFile = open(image.c_str(), O_RDWR);
    if (backingFile == -1) {
        throw SeparationFailedException("Failed to open backing image file at " + image);
    }

    if (ioctl(loopFileDescriptor, LOOP_SET_FD, backingFile) == -1) {
        throw SeparationFailedException("Failed to set LOOP_SET_FD on " + std::string(loopName));
    }

    if (mount(loopName, "/tmp/containerimage", "ext4", 0, nullptr) < 0) {
        throw SeparationFailedException("Failed to mount container image to /tmp/containerimage");
    }

    if (mount("proc", "/tmp/containerimage/proc", "proc", 0, nullptr) < 0) {
        throw SeparationFailedException("Failed to mount procfs. Are you root?");
    }
    if (chdir("/tmp/containerimage") < 0) {
        throw SeparationFailedException("Failed to chdir to /tmp/containerimage");
    }
    if (chroot("/tmp/containerimage") < 0) {
        throw SeparationFailedException("Failed to chroot to /tmp/containerimage");
    }
    if (chdir("/") < 0) {
        throw SeparationFailedException("Failed to chdir to /");
    }
}
