#include "layer.h"

#include <QImage>

#include <memory>

namespace playx::core {

layer::layer() {
    
}

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

}