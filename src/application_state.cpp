#include "layer.h"
#include "application_state.h"

#include <memory>
#include <vector>

namespace playx::core {

application_state::application_state()
{
    layer_container_ = std::vector<layer>();
}

std::vector<layer>& application_state::get_layer_container()
{
    return layer_container_;
}

void application_state::set_layer_container(std::vector<layer> layer_container)
{
    layer_container_ = layer_container;
}

}