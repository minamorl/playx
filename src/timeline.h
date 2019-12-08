#pragma once

#include "layer.h"
#include "keyframe_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>
#include <boost/optional.hpp>

#include <cstdint>
#include <iosfwd>
#include <vector>
#include <memory>

namespace playx::core {

using timeline_components = std::vector<
    std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>;

class timeline {
public:
    timeline(unit_frame timeline_length)
        : layer_counter_(0)
        , keyframe_container_()
        , layers_()
        , components_()
        , imap_()
        , length_(std::move(timeline_length))
    {}
    timeline_components get_keyframes_at(unit_frame f);
    boost::optional<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>> find_component(uint layer_idx, unit_frame keyframe_pos);
    std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>> find_or_create_component(uint layer_idx, unit_frame keyframe_start, unit_frame keyframe_end);
    std::vector<std::shared_ptr<layer>> get_all_layers();
    std::shared_ptr<layer> create_layer();
    void insert_keyframe(std::shared_ptr<keyframe> k, std::shared_ptr<layer> l);

    unit_frame get_length();
    void set_length(unit_frame length);

private:
    uint layer_counter_;
    keyframe_container keyframe_container_;
    std::vector<std::shared_ptr<layer>> layers_;
    timeline_components components_;

    boost::icl::split_interval_map<unit_frame, keyframe_container> imap_;

    unit_frame length_; 
};

}