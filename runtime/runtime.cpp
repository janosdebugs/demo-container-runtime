#include "plugin/SeparationProcessor.h"
#include "plugin/NetNamespaceSeparationPlugin.h"
#include "plugin/PidNamespaceSeparationPlugin.h"
#include "plugin/UtsNamespaceSeparationPlugin.h"

int main(char *const argv[]) {
    SeparationPlugin * plugins[] = {
        new NetNamespaceSeparationPlugin(),
        new PidNamespaceSeparationPlugin(),
        new UtsNamespaceSeparationPlugin()
    };
    SeparationProcessor separationProcessor = SeparationProcessor(
            plugins
    );
    separationProcessor.separate(argv);
}
