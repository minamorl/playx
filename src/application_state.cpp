#include "application_state.h"
#include "timeline.h"

#include <memory>

namespace playx::core {

timeline& application_state::get_timeline()
{
    return timeline_;
}

}