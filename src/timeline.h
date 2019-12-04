#pragma once

#include "layer.h"
#include "layer_container.h"
#include "unit_frame.h"

#include <boost/icl/split_interval_map.hpp>

#include <cstdint>
#include <iosfwd>

namespace playx::core {

class timeline {
public:
    timeline();
    std::vector<layer> get_current_layers(unit_frame f);

private:
    boost::icl::split_interval_map<unit_frame, layer_container> imap_;
};

}