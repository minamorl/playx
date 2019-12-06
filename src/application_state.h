#pragma once

#include "timeline.h"
#include "unit_frame.h"

#include <memory>

namespace playx::core {

class application_state {
public:
    timeline& get_timeline();
    
private:
    timeline timeline_;
    unit_frame current_frame_;
    uint current_layer_;
};

}