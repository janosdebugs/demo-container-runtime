#ifndef DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGIN_H

#include "SeparationFailedException.h"

class SeparationPlugin {
    public:
        virtual void beforeClone() throw(SeparationFailedException) = 0;
        virtual int getCloneFlags() = 0;
        virtual void afterClone() throw(SeparationFailedException) = 0;
};

#endif //DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGIN_H
