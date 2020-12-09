#include "../include/GaussianBlur/GaussianBlur.h"

bool GaussianBlur::init() {
    properties[GaussianBlurPlugin::SIGMA].display_type =
        PluginAPI::Property::DISPLAY_TYPE::COLOR_PICKER;
    return true;
}

bool GaussianBlur::deinit() { return true; }

void GaussianBlur::start_apply(PluginAPI::Canvas canvas,
                              PluginAPI::Position pos) {
    for (int64_t i = 0; i < canvas.height * canvas.width * sizeof(int32_t);
         i += 4) {

        GaussianBlurPlugin::Color* current_pixel =
            reinterpret_cast<GaussianBlurPlugin::Color*>(canvas.pixels + i);

        GaussianBlurPlugin::Color* filter_color =
            reinterpret_cast<GaussianBlurPlugin::Color*>(
                &properties[PluginAPI::Property::TYPE::PRIMARY_COLOR]
                     .int_value);

        current_pixel->r = std::min(current_pixel->r, filter_color->r);
        current_pixel->g = std::min(current_pixel->g, filter_color->g);
        current_pixel->b = std::min(current_pixel->b, filter_color->b);
        current_pixel->a = filter_color->a;
    }
}

void GaussianBlur::stop_apply(PluginAPI::Canvas canvas,
                             PluginAPI::Position pos) {}

void GaussianBlur::apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {}

extern "C" PluginAPI::Plugin* get_plugin() {
    return PluginAPI::get_instance<GaussianBlur>();
}
