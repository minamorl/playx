#pragma once

#include <QPainter>
#include <QColor>

#include <array>

namespace playx::tools {

class brush_state
{
public:
    brush_state(int size, std::array<float, 4> color_array)
        : size_(size)
        , color_(QColor::fromRgbF(color_array.at(0), color_array.at(1), color_array.at(2), color_array.at(3))) {}
    QColor color() const { return color_; }
    void color(std::array<float, 4> value) { color_ = QColor::fromRgbF(value.at(0), value.at(1), value.at(2), value.at(3)); }
    int size() const { return size_; }
    void size(int value) { size_ = value; }
private:
    QColor color_;
    int size_;
};

class brush
{
public:
    brush(QPainter& p, const brush_state& state) : p_(p), state_(state) {
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(Qt::NoPen);
        p.setBrush(state.color());
    }
    void paint(QPointF point);

private:
    QPainter& p_;
    const brush_state& state_;
};

}