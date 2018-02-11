#include <sched.h>
#include "UtsNamespaceSeparationPlugin.h"

int UtsNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWUTS;
}

void UtsNamespaceSeparationPlugin::beforeClone() throw(SeparationFailedException) {

}

void UtsNamespaceSeparationPlugin::afterClone() throw(SeparationFailedException) {

}
