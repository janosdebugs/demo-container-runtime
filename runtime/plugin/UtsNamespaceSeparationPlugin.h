#ifndef DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class UtsNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() throw (SeparationFailedException) override;

    void afterClone() throw (SeparationFailedException) override;

    int getCloneFlags() override;

    ~UtsNamespaceSeparationPlugin() override;
};


#endif //DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H
