#pragma once

#include "unit_frame.h"

#include <QImage>

#include <memory>

namespace playx::core {

class layer;

class keyframe {

public:
    keyframe(QImage image, unit_frame start, unit_frame end)
        : image_(std::move(image))
        , start_(std::move(start))
        , end_(std::move(end))
    {}
    QImage& get_image();
    boost::icl::discrete_interval<unit_frame> get_interval() const;

    bool operator==(keyframe const& other) const;


private:
    QImage image_;
    unit_frame start_;
    unit_frame end_;
};

}