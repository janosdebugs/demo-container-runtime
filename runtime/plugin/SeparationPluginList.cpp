
#include "SeparationPluginList.h"

SeparationPluginList::SeparationPluginList() {
    plugins = std::vector<SeparationPlugin *>();
}

SeparationPluginList::~SeparationPluginList() {
    /*for (auto plugin : plugins) {
        delete(plugin);
    }*/
}

void SeparationPluginList::add(SeparationPlugin * plugin) {
    plugins.emplace_back(plugin);
}

std::vector<SeparationPlugin *> SeparationPluginList::getPlugins() {
    return plugins;
}
