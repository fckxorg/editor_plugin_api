#include "../../../api/api.hpp"

namespace PluginAPI {
namespace TYPE {

constexpr Type ROUNDNESS = Type(COUNT);
constexpr Type ROTATION = Type(COUNT + 1);
constexpr Type AS_ERASER = Type(COUNT + 2);

};  // namespace TYPE
};  // namespace PluginAPI


class FancyBrush : public PluginAPI::Plugin {
    public:
    bool init() override;
    bool deinit() override;

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
    void start_apply(PluginAPI::Canvas canvas,
                     PluginAPI::Position pos) override;
    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

    private:
    int64_t prev_x;
    int64_t prev_y;
};