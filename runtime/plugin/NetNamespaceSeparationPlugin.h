#ifndef DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class NetNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() noexcept(false) override;

    void afterClone() noexcept(false) override;

    int getCloneFlags() override;

    ~NetNamespaceSeparationPlugin() override;
};

#endif //DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H
