#include "layer.h"
#include "unit_frame.h"

#include <QImage>

#include <memory>

namespace playx::core {

bool layer::operator==(layer const& other) const noexcept
{
    return this->keyframe_container_ == other.keyframe_container_;
}

std::shared_ptr<keyframe_container> layer::get_keyframe_container()
{
    return keyframe_container_;
}

void layer::insert_keyframe(keyframe keyframe)
{
    keyframe.set_layer(this);
}

bool layer::get_visibility_style() const
{
    return this->visibility_state_;
}

void layer::set_visibility_style(bool state)
{
    this->visibility_state_ = state;
}

uint layer::get_level()
{
    return level_;
}

void layer::set_level(uint level)
{
    level_ = level;
}
}