#include "../include/FancyBrush.hpp"

#include <cmath>
#include <cstdio>
bool FancyBrush::init() {
    properties[PluginAPI::TYPE::PRIMARY_COLOR].display_type =
        PluginAPI::Property::DISPLAY_TYPE::COLOR_PICKER;
    properties[PluginAPI::TYPE::SECONDARY_COLOR].display_type =
        PluginAPI::Property::DISPLAY_TYPE::COLOR_PICKER;
    properties[PluginAPI::TYPE::THICKNESS].display_type = PluginAPI::Property::DISPLAY_TYPE::SLIDER;
    properties[PluginAPI::TYPE::ROUNDNESS].display_type = PluginAPI::Property::DISPLAY_TYPE::SLIDER;
    properties[PluginAPI::TYPE::ROTATION].display_type = PluginAPI::Property::DISPLAY_TYPE::SLIDER;
    properties[PluginAPI::TYPE::AS_ERASER].display_type =
        PluginAPI::Property::DISPLAY_TYPE::CHECKBOX;

    properties[PluginAPI::TYPE::ROUNDNESS].label = "Roundness";
    properties[PluginAPI::TYPE::ROTATION].label = "Rotation";
    properties[PluginAPI::TYPE::AS_ERASER].label = "Use as eraser";

    return true;
}

bool FancyBrush::deinit() { return true; }

void FancyBrush::apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
    int64_t span = properties[PluginAPI::TYPE::THICKNESS].int_value;

    uint32_t *c = reinterpret_cast<uint32_t *>(canvas.pixels);
    uint32_t color = properties[PluginAPI::TYPE::AS_ERASER].int_value
                         ? properties[PluginAPI::TYPE::SECONDARY_COLOR].int_value
                         : properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value;
    double roundness = properties[PluginAPI::TYPE::ROUNDNESS].double_value;
    roundness *= roundness;

    int64_t delta_y = pos.y - prev_y;
    int64_t delta_x = pos.x - prev_x;

    uint64_t num_steps = (1 + std::max(std::abs(delta_x), std::abs(delta_y)));

    double x_step = static_cast<double>(delta_x) / num_steps;
    double y_step = static_cast<double>(delta_y) / num_steps;

    for (uint32_t i = 0; i < num_steps; i++) {
        double x_cur = prev_x + x_step * i;
        double y_cur = prev_y + y_step * i;
        int64_t x_from = std::max(x_cur - static_cast<double>(span), 0.0);
        int64_t y_from = std::max(y_cur - static_cast<double>(span), 0.0);

        int64_t x_to =
            std::min(static_cast<int64_t>(x_cur + span), static_cast<int64_t>(canvas.width - 1));
        int64_t y_to =
            std::min(static_cast<int64_t>(y_cur + span), static_cast<int64_t>(canvas.height - 1));


        for (int64_t y = y_from; y <= y_to; y++) {
            for (int64_t x = x_from; x <= x_to; x++) {
                double x_rel = static_cast<double>(x - x_cur);
                double y_rel = static_cast<double>(y - y_cur);

                double sin_phi = sin(M_PI * properties[PluginAPI::TYPE::ROTATION].double_value);
                double cos_phi = cos(M_PI * properties[PluginAPI::TYPE::ROTATION].double_value);

                double x_rot = cos_phi * x_rel + sin_phi * y_rel;
                double y_rot = sin_phi * x_rel - cos_phi * y_rel;

                if (x_rot * x_rot / (roundness * span * span)  + y_rot * y_rot / (span * span)  <= 1) {
                    c[y * canvas.width + x] = color;
                }
            }
        }
    }

    prev_y = pos.y;
    prev_x = pos.x;
}

void FancyBrush::start_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
    prev_x = pos.x;
    prev_y = pos.y;
    apply(canvas, pos);
}

void FancyBrush::stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
    apply(canvas, pos);
}

extern "C" PluginAPI::Plugin *get_plugin() { return PluginAPI::get_instance<FancyBrush>(); }
