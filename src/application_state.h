#pragma once

#include <memory>
#include <vector>
#include <layer.h>

namespace playx::core {

class application_state {
public:
    application_state();
    std::vector<layer>& get_layer_container();
    void set_layer_container(std::vector<layer> layer_container);
private:
    std::vector<layer> _layer_container;
};

}