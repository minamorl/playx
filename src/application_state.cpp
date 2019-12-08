#include "application_state.h"
#include "timeline.h"
#include "unit_frame.h"

#include <memory>
#include <iostream>

namespace playx::core {

timeline& application_state::get_timeline()
{
    return timeline_;
}

unit_frame application_state::get_current_frame()
{
    return current_frame_;
}

void application_state::set_current_frame(unit_frame frame)
{
    current_frame_ = frame;
}

std::shared_ptr<layer> application_state::current_layer()
{
    return get_timeline().get_all_layers().at(current_layer_index_);
}

std::shared_ptr<layer> application_state::change_current_layer_to(int current_layer_index)
{
    if (current_layer_index > static_cast<int>(maximum_layer_index())) {
        current_layer_index_ = maximum_layer_index();
    } else if (current_layer_index < 0) {
        current_layer_index_ = 0;
    } else {
        current_layer_index_ = current_layer_index;
    }
    return current_layer();
}

size_t application_state::maximum_layer_index() 
{
    return timeline_.get_all_layers().size() - 1;
}

}