#include <cstdint>

#include "api.hpp"

namespace GaussianBlurPlugin {

enum Parameters {
    SIGMA = PluginAPI::Property::TYPE::COUNT,
    RADIUS = PluginAPI::Property::TYPE::COUNT + 1,
    BORDER = PluginAPI::Property::TYPE::COUNT + 2
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
};  // namespace GaussianBlurPlugin

class GaussianBlur : public PluginAPI::Plugin {
   public:
    bool init() override;
    bool deinit() override;

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
    void start_apply(PluginAPI::Canvas canvas,
                     PluginAPI::Position pos) override;
    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
};

