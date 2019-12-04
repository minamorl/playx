#pragma once

#include "layer.h"

#include <memory>
#include <vector>

namespace playx::core {

class application_state {
public:
    application_state();
    std::vector<layer>& get_layer_container();
    void set_layer_container(std::vector<layer> layer_container);
private:
    std::vector<layer> layer_container_;
};

}