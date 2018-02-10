
#ifndef DEMO_CONTAINER_RUNTIME_SEPARATIONPROCESSOR_H
#define DEMO_CONTAINER_RUNTIME_SEPARATIONPROCESSOR_H

#include <vector>
#include "SeparationPlugin.h"

class SeparationProcessor {
private:
    SeparationPlugin ** plugins;
public:
    explicit SeparationProcessor(SeparationPlugin * plugins[]);
    void separate(char *const argv[]);
    SeparationPlugin ** getPlugins();
};

#endif //DEMO_CONTAINER_RUNTIME_SEPARATIONPROCESSOR_H
