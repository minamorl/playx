#pragma once

#include "layer.h"
#include "keyframe_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>

#include <cstdint>
#include <iosfwd>
#include <vector>
#include <memory>

namespace playx::core {

using timeline_components = std::vector<
    std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>;

class timeline {
public:
    timeline_components get_keyframes_at(unit_frame f);
    std::vector<std::shared_ptr<layer>> get_all_layers();
    std::shared_ptr<layer> create_layer();
    void insert_keyframe(std::shared_ptr<keyframe> k, std::shared_ptr<layer> l);
private:

    uint layer_counter_;
    keyframe_container keyframe_container_;
    std::vector<std::shared_ptr<layer>> layers_;
    timeline_components components_;

    boost::icl::split_interval_map<unit_frame, keyframe_container> imap_;
};

}