#pragma once

#include "layer.h"

#include <vector>
#include <iosfwd>

namespace playx::core {

class layer_container {
public:
    layer_container();
    layer_container(std::vector<layer> v);

    std::vector<layer> getLayers() const;
    void setLayers(std::vector<layer> v);

    layer_container& operator+=(layer_container const& other);
    bool operator==(layer_container const& other) const;
    friend std::ostream& operator<<(std::ostream& os, const layer_container& lc);

private:
    std::vector<layer> v_;
};

}