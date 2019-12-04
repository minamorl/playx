#include "timeline.h"
#include "layer_container.h"
#include "unit_frame.h"

#include <boost/icl/interval_map.hpp>
#include <boost/icl/right_open_interval.hpp>

#include <iostream>
#include <vector>


namespace playx::core {

timeline::timeline() : imap_() {}

std::vector<layer> timeline::get_current_layers(unit_frame f)
{
    f = unit_frame();
    using interval_type = boost::icl::interval<unit_frame>;
    imap_ += std::make_pair(
        interval_type::right_open(unit_frame(0), unit_frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    imap_ += std::make_pair(
        interval_type::right_open(unit_frame(1), unit_frame(5)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    imap_ += std::make_pair(
        interval_type::right_open(unit_frame(0), unit_frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));

    std::cout << imap_ << std::endl;
    return std::vector<layer>();
}

}
