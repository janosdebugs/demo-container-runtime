
#include <sched.h>
#include "NetNamespaceSeparationPlugin.h"

int NetNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWNET;
}
