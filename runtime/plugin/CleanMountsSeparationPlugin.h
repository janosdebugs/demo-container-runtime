#ifndef DEMO_CONTAINER_RUNTIME_CLEANMOUNTSSEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_CLEANMOUNTSSEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class CleanMountsSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() noexcept(false) override;

    int getCloneFlags() override;

    void afterClone() noexcept(false) override;

    ~CleanMountsSeparationPlugin() override;
};


#endif //DEMO_CONTAINER_RUNTIME_CLEANMOUNTSSEPARATIONPLUGIN_H
