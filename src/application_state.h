#pragma once

#include "timeline.h"
#include "unit_frame.h"
#include "timer.h"

#include <memory>

namespace playx::core {

class application_state {
public:
    timeline& get_timeline();
    unit_frame get_current_frame();
    std::shared_ptr<layer> current_layer();
    std::shared_ptr<layer> change_current_layer_to(int current_layer_index);
    size_t maximum_layer_index();
    
private:
    timeline timeline_;
    unit_frame current_frame_;
    size_t current_layer_index_;
    bool is_timer_working_;
};

}