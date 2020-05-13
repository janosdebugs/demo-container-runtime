#ifndef DEMO_CONTAINER_RUNTIME_PIDNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_PIDNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class PidNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() throw (SeparationFailedException) override;

    int getCloneFlags() override;

    void afterClone() throw (SeparationFailedException) override;

    ~PidNamespaceSeparationPlugin() override;
};


#endif //DEMO_CONTAINER_RUNTIME_PIDNAMESPACESEPARATIONPLUGIN_H
