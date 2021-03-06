#pragma once

#include "timeline.h"
#include "unit_frame.h"
#include "timer.h"
#include "brush.h"

#include <memory>

namespace playx::core {

class application_state {
public:
    application_state(timeline tl, playx::tools::brush_state brush_state)
        : timeline_(std::move(tl))
        , current_frame_(0)
        , current_layer_index_(0)
        , brush_state_(brush_state)
        , is_timer_working_(false)
    {}
    timeline& tl();
    unit_frame current_frame();
    void current_frame(unit_frame frame);
    std::shared_ptr<layer> current_layer();
    std::shared_ptr<layer> change_current_layer_to(int current_layer_index);
    size_t maximum_layer_index();
    playx::tools::brush_state& brush_state() { return brush_state_; }

private:
    playx::core::timeline timeline_;
    unit_frame current_frame_;
    size_t current_layer_index_;
    playx::tools::brush_state brush_state_;
    bool is_timer_working_;

};

}