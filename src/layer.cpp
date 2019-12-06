#include "layer.h"
#include "unit_frame.h"

#include <QImage>

#include <memory>

namespace playx::core {

bool layer::operator==(layer const& other) const noexcept
{
    return this->level_ == other.level_;
}

bool layer::get_visibility_style() const
{
    return this->visibility_state_;
}

void layer::set_visibility_style(bool state)
{
    this->visibility_state_ = state;
}

uint layer::get_level() const
{
    return level_;
}

void layer::set_level(uint level)
{
    level_ = level;
}
}