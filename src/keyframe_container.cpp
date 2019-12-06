#include "keyframe_container.h"

#include <boost/icl/type_traits/identity_element.hpp>

#include <iostream>

namespace playx::core {


std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>& keyframe_container::get_keyframes()
{
    return v_;
}

size_t keyframe_container::size() const noexcept
{
    return v_.size();
}

keyframe_container& keyframe_container::operator+=(keyframe_container const& other)
{
    auto other_layer = other.v_;
    v_.insert(v_.end(), other_layer.begin(), other_layer.end());
    return *this;
}
bool keyframe_container::operator==(keyframe_container const& other) const
{
    return v_ == other.v_;
}
std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>& keyframe_container::operator()()
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