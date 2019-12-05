#pragma once

#include "unit_frame.h"

#include <QImage>

#include <memory>

namespace playx::core {

class layer;

class keyframe {

public:
    keyframe() = delete;
    keyframe(QImage image, layer* layer, unit_frame start, unit_frame end);
    layer* get_layer();
    void set_layer(layer* layer);
    QImage& get_image();
    boost::icl::discrete_interval<unit_frame> get_interval() const;

    bool operator==(keyframe const& other) const;


private:
    QImage image_;
    layer* layer_;
    unit_frame start_;
    unit_frame end_;
};

}