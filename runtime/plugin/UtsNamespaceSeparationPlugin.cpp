#include <sched.h>
#include "UtsNamespaceSeparationPlugin.h"

int UtsNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWUTS;
}
