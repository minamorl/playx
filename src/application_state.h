#pragma once

#include "timeline.h"

#include <memory>

namespace playx::core {

class application_state {
public:
    application_state();
    timeline& get_timeline();
    
private:
    timeline timeline_;
};

}