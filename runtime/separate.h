#ifndef DEMO_CONTAINER_RUNTIME_SEPARATE_H
#define DEMO_CONTAINER_RUNTIME_SEPARATE_H

#include <vector>
#include <string>
#include "plugin/SeparationPlugin.h"
#include "plugin/SeparationPluginList.h"

int run_separated(const SeparationPluginList &pluginList, const std::vector<std::string> &argvList);

#endif //DEMO_CONTAINER_RUNTIME_SEPARATE_H
