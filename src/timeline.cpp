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

    // imap_ += std::make_pair(
    //     interval_type::right_open(unit_frame(0), unit_frame(3)),
    //     playx::core::layer_container(std::vector<layer>{layer()}));
    // imap_ += std::make_pair(
    //     interval_type::right_open(unit_frame(1), unit_frame(5)),
    //     playx::core::layer_container(std::vector<layer>{layer()}));
    // imap_ += std::make_pair(
    //     interval_type::right_open(unit_frame(5), unit_frame(1)),
    //     playx::core::layer_container(std::vector<layer>{layer()}));

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
