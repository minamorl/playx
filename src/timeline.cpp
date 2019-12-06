#include "timeline.h"
#include "keyframe_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>

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
        std::cout << "Nothing found" << std::endl;
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

void timeline::insert_keyframe(std::shared_ptr<keyframe> k, std::shared_ptr<layer> l)
{
    components_.emplace_back(l, k);
}

}
