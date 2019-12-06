#pragma once

#include "unit_frame.h"
#include "keyframe_container.h"
#include "keyframe.h"

#include <QImage>

#include <boost/icl/split_interval_map.hpp>

#include <memory>
#include <iosfwd>

namespace playx::core {

class layer {

public:
    layer() = default;
    layer(uint level)
        : level_(level)
    {}
    bool operator==(layer const& other) const noexcept;
    bool get_visibility_style() const;
    void set_visibility_style(bool state);
    uint get_level() const;
    void set_level(uint level);
private:
    bool visibility_state_ = true;
    uint level_;
};

}