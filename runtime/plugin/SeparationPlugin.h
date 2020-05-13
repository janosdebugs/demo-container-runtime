#ifndef DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGIN_H

#include "SeparationFailedException.h"

class SeparationPlugin {
    public:
        virtual void beforeClone() noexcept(false) = 0;
        virtual int getCloneFlags() = 0;
        virtual void afterClone() noexcept(false) = 0;
        virtual ~SeparationPlugin() = default;
};

#endif //DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGIN_H
