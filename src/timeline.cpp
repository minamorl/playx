#include "timeline.h"
#include "layer_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>

#include <iostream>
#include <vector>


namespace playx::core {

timeline::timeline() : imap_() {}

std::vector<layer> timeline::get_current_layers(unit_frame f)
{
    f = unit_frame(5);
    using interval_type = boost::icl::interval<unit_frame>;
    
    imap_ += std::make_pair(
        interval_type::right_open(unit_frame(0), unit_frame(3)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    imap_ += std::make_pair(
        interval_type::right_open(unit_frame(1), unit_frame(5)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    imap_ += std::make_pair(
        interval_type::right_open(unit_frame(0), unit_frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));

    std::cout << imap_ << std::endl;

    auto x = imap_.find(interval_type::closed(unit_frame(7), unit_frame(7)));
    playx::core::layer_container b = x->second;
    std::cout << b << std::endl;
    return std::vector<layer>();
}

}
