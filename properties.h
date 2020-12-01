#include <cstdint>
#include <string>
#include <unordered_map>

namespace PluginAPI {
struct Canvas {
    uint8_t* pixels;

    size_t height;
    size_t width;
};

struct Position {
    int64_t x;
    int64_t y;
};

struct Property {
    enum TYPE { PRIMARY_COLOR, SECONDARY_COLOR, THICKNESS };
    enum DISPLAY_TYPE { COLOR_PICKER, SLIDER, INPUTBOX, CHECKBOX };

    DISPLAY_TYPE display_type;

    union {
        int32_t int_value;
        double double_value;
        void* pointer_value;
    };
};

struct PluginInfo {
    uint16_t version;
    std::string name;
};

class Plugin {
   public:
    using property_map = std::unordered_map<Property::TYPE, Property>;
    property_map properties;

    virtual void init() = 0;  // настройки отрисовки графических элементов,
                              // проверка поддержки
    virtual void deinit() = 0;
    virtual void apply(Canvas canvas, Position pos) = 0;
    virtual void start_apply(Canvas canvas, Position pos) = 0;
    virtual void stop_apply(Canvas canvas, Position pos) = 0;
};
}  // namespace PluginAPI
