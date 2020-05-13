#ifndef DEMO_CONTAINER_RUNTIME_MOUNTIMAGESEPARATIONPLUGIN_H
#define DEMO_CONTAINER_RUNTIME_MOUNTIMAGESEPARATIONPLUGIN_H

#include <cstring>
#include "SeparationPlugin.h"

class MountImageSeparationPlugin: public SeparationPlugin {
private:
    std::string image;
public:
    explicit MountImageSeparationPlugin(const std::string &image);

    void beforeClone() throw (SeparationFailedException) override;

    int getCloneFlags() override;

    void afterClone() throw (SeparationFailedException) override;

    ~MountImageSeparationPlugin() override;
};


#endif //DEMO_CONTAINER_RUNTIME_MOUNTIMAGESEPARATIONPLUGIN_H
