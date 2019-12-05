#include "timeline.h"
#include "keyframe_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>

#include <iostream>
#include <vector>


namespace playx::core {

timeline::timeline() : imap_() {}

keyframe_container timeline::get_keyframes_at(unit_frame f)
{
    using interval_type = boost::icl::interval<unit_frame>;

    for (auto layer : layers_) {
        for (auto kf : layer.get_keyframe_container()->get_keyframes()) {
            imap_ += std::make_pair(
                kf.get_interval(), keyframe_container(std::vector<keyframe>{kf})
            );
        }
    }
    std::cout << imap_ << std::endl;

    auto it = imap_.find(interval_type::closed(f, f));
    if (it == imap_.end()) {
        std::cout << "Nothing found" << std::endl;
        return keyframe_container();
    }
    std::cout << it->second << std::endl;
    
    return it->second;
}

std::vector<layer>& timeline::get_all_layers()
{
    return layers_;
}

layer& timeline::create_layer()
{
    layer l(layer_counter_);
    layers_.push_back(l);
    layer_counter_++;
    return layers_.at(layers_.size() - 1);
}

}
