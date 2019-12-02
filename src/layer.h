#pragma once

#include <memory>
#include <QImage>

namespace playx::core {

enum class visibility_state {
    VISIBLE,
    HIDDEN,
};

class layer {

public:
    layer(QImage image, int32_t level);
    visibility_state get_visibility_style() const;
    void set_visibility_style(visibility_state state);
    QImage& get_image();
    void set_image(QImage image);

private:
    QImage _image;
    visibility_state _state = visibility_state::VISIBLE;
    int32_t _level;
};

}