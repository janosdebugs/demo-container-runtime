#ifndef DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class NetNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() throw (SeparationFailedException) override;

    void afterClone() throw (SeparationFailedException) override;

    int getCloneFlags() override;

    ~NetNamespaceSeparationPlugin() override;
};

#endif //DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H
