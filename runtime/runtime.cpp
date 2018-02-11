#include <iostream>
#include "separate.h"
#include "plugin/NetNamespaceSeparationPlugin.h"
#include "plugin/PidNamespaceSeparationPlugin.h"
#include "plugin/UtsNamespaceSeparationPlugin.h"
#include "plugin/MountNamespaceSeparationPlugin.h"
#include "plugin/MountImageSeparationPlugin.h"
#include "plugin/CleanMountsSeparationPlugin.h"

int main(int argl, char * argv[]) {
    if (argl < 3) {
        std::cerr << "Usage: demo_runtime container.img executable-in-container" << std::endl;
        return -1;
    }

    try {
        auto image = std::string(argv[1]);

        auto oopArgv = std::vector<std::string>();
        //Ignore the first element so we run a program inside the container, not this program again.
        for (int i = 2; i < argl; i++) {
            oopArgv.emplace_back(argv[i]);
        }

        auto plugins = SeparationPluginList();
        plugins.add(new PidNamespaceSeparationPlugin());
        plugins.add(new MountNamespaceSeparationPlugin());
        plugins.add(new NetNamespaceSeparationPlugin());
        plugins.add(new UtsNamespaceSeparationPlugin());
        plugins.add(new CleanMountsSeparationPlugin());
        plugins.add(new MountImageSeparationPlugin(image));

        return run_separated(plugins, oopArgv);
    } catch (SeparationFailedException &e) {
        std::cerr << e.what() << std::endl;
    }
}
