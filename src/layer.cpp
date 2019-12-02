#include <layer.h>
#include <memory>
#include <QImage>

namespace playx::core {

layer::layer(QImage image, int32_t level) : _image(image), _level(level) {

}

visibility_state layer::get_visibility_style() const
{
    return this->_state;
}

void layer::set_visibility_style(visibility_state state)
{
    this->_state = state;
}

QImage& layer::get_image()
{
    return this->_image;
}

void layer::set_image(QImage image)
{
    this->_image = image;
}

}