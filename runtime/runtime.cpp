#include <iostream>
#include "separate.h"
#include "plugin/NetNamespaceSeparationPlugin.h"
#include "plugin/PidNamespaceSeparationPlugin.h"
#include "plugin/UtsNamespaceSeparationPlugin.h"
#include "plugin/MountSeparationPlugin.h"

int main(int argl, char * argv[]) {
    auto plugins = SeparationPluginList();
    plugins.add(new MountSeparationPlugin());
    plugins.add(new NetNamespaceSeparationPlugin());
    plugins.add(new PidNamespaceSeparationPlugin());
    plugins.add(new UtsNamespaceSeparationPlugin());

    auto oopArgv = std::vector<std::string>();
    //Ignore the first element so we run a program inside the container, not this program again.
    for (int i = 1; i < argl; i++) {
        oopArgv.emplace_back(argv[i]);
    }

    return run_separated(plugins, oopArgv);
}
