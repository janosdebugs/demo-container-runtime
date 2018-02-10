//
// Created by root on 10.02.18.
//

#include <sched.h>
#include <sys/mount.h>

#include "PidNamespaceSeparationPlugin.h"

void PidNamespaceSeparationPlugin::beforeClone() throw(SeparationFailedException) {

}

int PidNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWPID;
}

void PidNamespaceSeparationPlugin::afterClone() throw(SeparationFailedException) {
    if (mount("proc", "/proc", "proc", 0, nullptr) < 0) {
        throw SeparationFailedException();
    }
}
