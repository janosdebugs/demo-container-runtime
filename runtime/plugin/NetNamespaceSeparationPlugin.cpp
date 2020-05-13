
#include <sched.h>
#include "NetNamespaceSeparationPlugin.h"

int NetNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWNET;
}

void NetNamespaceSeparationPlugin::beforeClone() noexcept(false) {

}

void NetNamespaceSeparationPlugin::afterClone() noexcept(false) {

}

NetNamespaceSeparationPlugin::~NetNamespaceSeparationPlugin() = default;
