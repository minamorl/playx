#include "layer_container.h"

#include <iostream>

namespace playx::core {

layer_container::layer_container(std::vector<layer> v) : v_(v)
{
}

std::vector<layer> layer_container::get_layers() const
{
    return v_;
}

void layer_container::set_layers(std::vector<layer> v)
{
    v_ = v;
}

layer_container& layer_container::operator+=(layer_container const& other)
{
    std::cout << "operator+=" << std::endl;
    std::cout << v_.size() << std::endl;
    std::cout << other.v_.size() << std::endl;
    auto other_layer = other.v_;
    v_.insert(v_.end(), other_layer.begin(), other_layer.end());
    return *this;
}
bool layer_container::operator==(layer_container const& other) const
{
    return v_ == other.v_;
}
std::ostream& operator<<(std::ostream& os, layer_container const& lc)
{
    os << "[";
    for (auto it = lc.v_.begin(); it != lc.v_.end(); ++it) {
        os << "image" << ",";
    }
    os << "]";
    return os;
}
}
