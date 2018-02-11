
#ifndef DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGINLIST_H
#define DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGINLIST_H

#include <vector>
#include <memory>
#include "SeparationPlugin.h"

class SeparationPluginList {
private:
    std::vector<SeparationPlugin *> plugins;
public:
    SeparationPluginList();
    ~SeparationPluginList();
    void add(SeparationPlugin * plugin);
    std::vector<SeparationPlugin *> getPlugins();
};


#endif //DEMO_CONTAINER_RUNTIME_SEPARATIONPLUGINLIST_H
