#include <sched.h>
#include <string>
#include <sys/mount.h>

#include "PidNamespaceSeparationPlugin.h"

void PidNamespaceSeparationPlugin::beforeClone() throw(SeparationFailedException) {

}

int PidNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWPID;
}

void PidNamespaceSeparationPlugin::afterClone() throw(SeparationFailedException) {

}
