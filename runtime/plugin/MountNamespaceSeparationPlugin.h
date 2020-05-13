#ifndef DEMO_CONTAINER_RUNTIME_MOUNTNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_MOUNTNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class MountNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() noexcept(false) override;

    int getCloneFlags() override;

    void afterClone() noexcept(false) override;

    ~MountNamespaceSeparationPlugin() override;
};

#endif //DEMO_CONTAINER_RUNTIME_MOUNTNAMESPACESEPARATIONPLUGIN_H
