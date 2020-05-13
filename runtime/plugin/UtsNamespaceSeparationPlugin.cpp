#include <sched.h>
#include "UtsNamespaceSeparationPlugin.h"

int UtsNamespaceSeparationPlugin::getCloneFlags() {
    return CLONE_NEWUTS;
}

void UtsNamespaceSeparationPlugin::beforeClone() noexcept(false) {

}

void UtsNamespaceSeparationPlugin::afterClone() noexcept(false) {

}

UtsNamespaceSeparationPlugin::~UtsNamespaceSeparationPlugin() = default;
