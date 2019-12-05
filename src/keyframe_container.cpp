#include "keyframe_container.h"

#include <boost/icl/type_traits/identity_element.hpp>

#include <iostream>

namespace playx::core {

keyframe_container::keyframe_container(std::vector<keyframe> v) : v_(v)
{
}

std::vector<keyframe>& keyframe_container::get_keyframes()
{
    return v_;
}

void keyframe_container::push_back(keyframe l)
{
    v_.push_back(l);
}

size_t keyframe_container::size() const
{
    return v_.size();
}


keyframe_container& keyframe_container::operator+=(keyframe_container const& other)
{
    std::cout << "operator+=" << std::endl;
    std::cout << v_.size() << std::endl;
    std::cout << other.v_.size() << std::endl;
    auto other_layer = other.v_;
    v_.insert(v_.end(), other_layer.begin(), other_layer.end());
    return *this;
}
bool keyframe_container::operator==(keyframe_container const& other) const
{
    return v_ == other.v_;
}
std::vector<keyframe>& keyframe_container::operator()()
{
    return v_;
}
std::ostream& operator<<(std::ostream& os, keyframe_container const& lc)
{
    os << "[";
    for (auto it = lc.v_.begin(); it != lc.v_.end(); ++it) {
        os << "image" << ",";
    }
    os << "]";
    return os;
}

}