#include "application_state.h"
#include "timeline.h"

#include <memory>

namespace playx::core {

application_state::application_state()
{
    timeline_ = timeline();
}

timeline& application_state::get_timeline()
{
    return timeline_;
}

}