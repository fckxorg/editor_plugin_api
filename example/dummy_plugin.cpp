#include <iostream>
#include "properties.h"


class DummyPlugin : public PluginAPI::Plugin {
    void init() {
        std::cout << "Plugin initialized\n";
    }

    void deinit() {
        std::cout << "Plugin deinitialized\n";
    }

    void start_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
        std::cout << "Plugin application started\n";
    }

    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
        std::cout << "Plugin application finished\n";
    }

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
        std::cout << "Applying...\n";
    }
};

extern "C" std::unique_ptr<PluginAPI::Plugin> instantiate() {
   return std::unique_ptr<PluginAPI::Plugin>(new DummyPlugin());
}
