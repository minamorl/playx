#pragma once

#include <QImage>

#include <memory>

namespace playx::core {

class layer {

public:
    layer();
    layer(QImage image, int32_t level);
    bool operator==(layer const& other) const noexcept;
    bool get_visibility_style() const;
    void set_visibility_style(bool state);
    QImage& get_image();
    void set_image(QImage image);

private:
    QImage image_;
    bool state_ = true;
    int32_t level_;
};

}