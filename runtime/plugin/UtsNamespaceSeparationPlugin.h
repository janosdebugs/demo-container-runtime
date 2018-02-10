#ifndef DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class UtsNamespaceSeparationPlugin: public SeparationPlugin {
public:
    int getCloneFlags() override;
};


#endif //DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H
