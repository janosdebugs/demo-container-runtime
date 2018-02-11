#ifndef DEMO_CONTAINER_RUNTIME_MOUNTSEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_MOUNTSEPARATIONPLUGIN_H

#include "SeparationPlugin.h"

class MountSeparationPlugin: public SeparationPlugin {
public:
    void beforeClone() throw(SeparationFailedException) override;

    int getCloneFlags() override;

    void afterClone() throw(SeparationFailedException) override;
};

#endif //DEMO_CONTAINER_RUNTIME_MOUNTSEPARATIONPLUGIN_H
