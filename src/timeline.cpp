#include "timeline.h"
#include "keyframe_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>
#include <boost/optional.hpp>

#include <iostream>
#include <vector>


namespace playx::core {

timeline_components timeline::get_keyframes_at(unit_frame f)
{
    using interval_type = boost::icl::interval<unit_frame>;

    imap_.clear();

    for (auto& tp : components_) {
        imap_ += std::make_pair(
            tp.second->get_interval(), keyframe_container(std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>{tp}));
    }
    
    std::cout << imap_ << std::endl;

    auto it = imap_.find(interval_type::closed(f, f));
    if (it == imap_.end()) {
        return timeline_components();
    }
    std::cout << it->second << std::endl;
    return static_cast<keyframe_container>(it->second).get_keyframes();
}



std::vector<std::shared_ptr<layer>> timeline::get_all_layers()
{
    std::sort(layers_.begin(), layers_.end(), [](std::shared_ptr<layer> x, std::shared_ptr<layer> y) {return x->get_level() < y->get_level();});
    return layers_;
}

std::shared_ptr<layer> timeline::create_layer()
{
    auto l = std::make_shared<layer>(layer_counter_);
    layers_.push_back(l);
    layer_counter_++;
    return layers_.at(layers_.size() - 1);
}

boost::optional<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>> timeline::find_component(uint layer_idx, unit_frame keyframe_pos)
{
    auto const kfs = get_keyframes_at(keyframe_pos);
    auto it = std::find_if(kfs.begin(), kfs.end(), [&](std::pair<std::shared_ptr<playx::core::layer>, std::shared_ptr<playx::core::keyframe>> const& c) {
        return c.first->get_level() == layer_idx;
    });
    if (it == kfs.end()) {
        return boost::none;
    }
    return std::make_pair(it->first, it->second);
}

std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>> timeline::find_or_create_component(uint layer_idx, unit_frame keyframe_start, unit_frame keyframe_end)
{
    auto const kfs = get_keyframes_at(keyframe_start);
    auto it = std::find_if(kfs.begin(), kfs.end(), [&](std::pair<std::shared_ptr<playx::core::layer>, std::shared_ptr<playx::core::keyframe>> const& c) {
        return c.first->get_level() == layer_idx;
    });
    if (it == kfs.end()) {
        auto image = QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied);
        image.fill(Qt::transparent);
        std::shared_ptr<keyframe> kf = std::make_shared<playx::core::keyframe>(image, keyframe_start, keyframe_end);
        std::shared_ptr<layer> l = std::make_shared<layer>(layer_idx);
        insert_keyframe(kf, l);
        return std::make_pair(l, kf);
    }
    return std::make_pair(it->first, it->second);
}

void timeline::insert_keyframe(std::shared_ptr<keyframe> k, std::shared_ptr<layer> l)
{
    components_.emplace_back(l, k);
}

unit_frame timeline::get_length()
{
    return length_;
}

void timeline::set_length(unit_frame length)
{
    length_ = length;
}

}
