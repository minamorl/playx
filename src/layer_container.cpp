#include <layer_container.h>
#include <iostream>

namespace playx::core {

layer_container::layer_container() : _v{}
{}

layer_container::layer_container(std::vector<layer> v) : _v(v)
{}

std::vector<layer> layer_container::getLayers() const
{
    return _v;
}

void layer_container::setLayers(std::vector<layer> v)
{
    _v = v;
}

layer_container& layer_container::operator+=(layer_container const& other)
{
    std::cout << _v.size() << std::endl;
    std::cout << other.getLayers().size() << std::endl;
    auto other_layer = other.getLayers();
    _v.insert(_v.end(), other_layer.begin(), other_layer.end());
    return *this;
}

bool layer_container::operator==(layer_container const& other) const
{
    return _v == other.getLayers();
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
