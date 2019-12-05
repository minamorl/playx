#pragma once

#include "layer.h"
#include "keyframe_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace playx::core {

class timeline {
public:
    keyframe_container get_keyframes_at(unit_frame f);
    std::vector<layer>& get_all_layers();
    layer& create_layer();

private:
    uint layer_counter_;
    std::vector<layer> layers_;
    boost::icl::split_interval_map<unit_frame, keyframe_container> imap_;
};

}