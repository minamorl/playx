#include "layer.h"
#include "unit_frame.h"

#include <QImage>

#include <memory>

namespace playx::core {

layer::layer(unit_frame start, unit_frame end) : start_(start), end_(end)
{}

layer::layer(QImage image, int32_t level) : image_(image), level_(level) {

}

bool layer::operator==(layer const& other) const noexcept
{
    return this->image_ == other.image_;
}


bool layer::get_visibility_style() const
{
    return this->state_;
}

void layer::set_visibility_style(bool state)
{
    this->state_ = state;
}

QImage& layer::get_image()
{
    return this->image_;
}

void layer::set_image(QImage image)
{
    this->image_ = image;
}

boost::icl::discrete_interval<unit_frame> layer::get_interval() const {
    auto interval = boost::icl::interval<unit_frame>::right_open(start_, end_);
    return interval;
}

}