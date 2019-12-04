#pragma once

#include "unit_frame.h"

#include <QImage>

#include <boost/icl/split_interval_map.hpp>

#include <memory>
#include <iosfwd>

namespace playx::core {

class layer {

public:
    layer() = default;
    layer(unit_frame start, unit_frame end);
    layer(QImage image, int32_t level);
    bool operator==(layer const& other) const noexcept;
    bool get_visibility_style() const;
    void set_visibility_style(bool state);
    QImage& get_image();
    void set_image(QImage image);
    boost::icl::discrete_interval<unit_frame> get_interval() const;

private:
    QImage image_;
    bool state_ = true;
    int32_t level_;

    unit_frame start_;
    unit_frame end_;
};

}