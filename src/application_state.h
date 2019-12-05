#pragma once

#include "timeline.h"

#include <memory>

namespace playx::core {

class application_state {
public:
    timeline& get_timeline();
    
private:
    timeline timeline_;
};

}