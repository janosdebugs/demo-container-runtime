#ifndef DEMO_CONTAINER_RUNTIME_PIDNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_PIDNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class PidNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() noexcept(false) override;

    int getCloneFlags() override;

    void afterClone() noexcept(false) override;

    ~PidNamespaceSeparationPlugin() override;
};


#endif //DEMO_CONTAINER_RUNTIME_PIDNAMESPACESEPARATIONPLUGIN_H
