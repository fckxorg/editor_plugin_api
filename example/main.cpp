#include <dlfcn.h>

#include <memory>
#include <cstdio>

#include "properties.h"

int main(int argc, const char** argv) {
    std::unique_ptr<PluginAPI::Plugin> (*instantiator)();

    void* handle = nullptr;

    if ((handle = dlopen(argv[1], RTLD_NOW)) == NULL) {
        printf("%s\n", dlerror()); 
        return 1;
    }

    instantiator = reinterpret_cast<std::unique_ptr<PluginAPI::Plugin> (*)()>(
        dlsym(handle, "instantiate"));

    if(dlerror() != NULL) {
        perror("Function not found");
        dlclose(handle);
        return 2;
    }

    std::unique_ptr<PluginAPI::Plugin> my_fancy_plugin = instantiator();

    my_fancy_plugin->init();

    dlclose(handle);
    return 0;
}
