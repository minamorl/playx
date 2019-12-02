#pragma once

#include <memory>
#include <QImage>

namespace playx::core {

class layer {

public:
    layer(QImage image, int32_t level);
    bool get_visibility_style() const;
    void set_visibility_style(bool state);
    QImage& get_image();
    void set_image(QImage image);

private:
    QImage _image;
    bool _state = true;
    int32_t _level;
};

}