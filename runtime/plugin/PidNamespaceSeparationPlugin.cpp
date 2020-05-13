#include <sched.h>
#include <string>
#include <sys/mount.h>

#include "PidNamespaceSeparationPlugin.h"

void PidNamespaceSeparationPlugin::beforeClone() noexcept(false) {

}

int PidNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWPID;
}

void PidNamespaceSeparationPlugin::afterClone() noexcept(false) {

}

PidNamespaceSeparationPlugin::~PidNamespaceSeparationPlugin() = default;