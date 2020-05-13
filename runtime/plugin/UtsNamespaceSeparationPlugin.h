#ifndef DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class UtsNamespaceSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() noexcept(false) override;

    void afterClone() noexcept(false) override;

    int getCloneFlags() override;

    ~UtsNamespaceSeparationPlugin() override;
};


#endif //DEMO_CONTAINER_RUNTIME_UTSNAMESPACESEPARATIONPLUGIN_H
