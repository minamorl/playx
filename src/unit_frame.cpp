#include "unit_frame.h"

namespace playx::core {

uint32_t unit_frame::get_index() const
{
    return index_;
}

void unit_frame::set_index(uint32_t frame)
{
    index_ = frame;
}

bool unit_frame::operator==(unit_frame const& other) const noexcept {
    return index_ == other.get_index();
}

bool unit_frame::operator<(unit_frame const& other) const noexcept {
    return index_ < other.get_index();
}

std::ostream& operator<<(std::ostream& os, const unit_frame& f)
{
    os << f.get_index();
    return os;
}

}