#ifndef DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class NetNamespaceSeparationPlugin: public SeparationPlugin {
public:
    int getCloneFlags() override;
};


#endif //DEMO_CONTAINER_RUNTIME_NETNAMESPACESEPARATIONPLUGIN_H
