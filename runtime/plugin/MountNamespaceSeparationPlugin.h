#ifndef DEMO_CONTAINER_RUNTIME_MOUNTNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_MOUNTNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class MountNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() throw(SeparationFailedException) override;

    int getCloneFlags() override;

    void afterClone() throw(SeparationFailedException) override;
};

#endif //DEMO_CONTAINER_RUNTIME_MOUNTNAMESPACESEPARATIONPLUGIN_H
