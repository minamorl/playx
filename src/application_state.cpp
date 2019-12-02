#include <memory>
#include <vector>
#include <layer.h>
#include <application_state.h>

namespace playx::core {

application_state::application_state()
{
    _layer_container = std::vector<layer>();
}

std::vector<layer>& application_state::get_layer_container()
{
    return _layer_container;
}

void application_state::set_layer_container(std::vector<layer> layer_container)
{
    _layer_container = layer_container;
}

}