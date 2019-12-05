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
    layer(uint level)
        : level_(level)
        , keyframe_container_(std::make_shared<keyframe_container>())
    {}
    
    bool operator==(layer const& other) const noexcept;
    bool get_visibility_style() const;
    void set_visibility_style(bool state);
    std::shared_ptr<keyframe_container> get_keyframe_container();
    void insert_keyframe(keyframe keyframe);
    uint get_level();
    void set_level(uint level);
private:
    bool visibility_state_ = true;
    uint level_;
    std::shared_ptr<keyframe_container> keyframe_container_;
};

}