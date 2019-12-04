#include "layer_container.h"

#include <iostream>

namespace playx::core {

layer_container::layer_container() : v_{}
{}

layer_container::layer_container(std::vector<layer> v) : v_(v)
{}

std::vector<layer> layer_container::getLayers() const
{
    return v_;
}

void layer_container::setLayers(std::vector<layer> v)
{
    v_ = v;
}

layer_container& layer_container::operator+=(layer_container const& other)
{
    std::cout << v_.size() << std::endl;
    std::cout << other.getLayers().size() << std::endl;
    auto other_layer = other.getLayers();
    v_.insert(v_.end(), other_layer.begin(), other_layer.end());
    return *this;
}

bool layer_container::operator==(layer_container const& other) const
{
    return v_ == other.getLayers();
}
std::ostream& operator<<(std::ostream& os, const layer_container& lc)
{
    os << "[";
    for (uint i = 0; i < lc.getLayers().size(); i++) {
        os << "image" << i << ",";
    }
    os << "]";
    return os;
}
}
