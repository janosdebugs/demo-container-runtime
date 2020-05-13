
#include <sched.h>
#include "NetNamespaceSeparationPlugin.h"

int NetNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWNET;
}

void NetNamespaceSeparationPlugin::beforeClone() throw (SeparationFailedException) {

}

void NetNamespaceSeparationPlugin::afterClone() throw (SeparationFailedException) {

}

NetNamespaceSeparationPlugin::~NetNamespaceSeparationPlugin() = default;
