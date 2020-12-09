#include <cstdint>
#include <vector>

#include "../../../../api/api.hpp"

namespace PluginAPI {
namespace TYPE {

constexpr Type SIGMA = Type(COUNT);
constexpr Type RADIUS = Type(COUNT + 1);
constexpr Type BORDER = Type(COUNT + 2);

};  // namespace TYPE
};  // namespace PluginAPI

namespace GaussianBlurPlugin {

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
};  // namespace GaussianBlurPlugin

struct Kernel {
   int32_t size = 0; 
    
   std::vector<float> weights;
};

class GaussianBlur : public PluginAPI::Plugin {
   public:
    bool init() override;
    bool deinit() override;

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
    void start_apply(PluginAPI::Canvas canvas,
                     PluginAPI::Position pos) override;
    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
};

