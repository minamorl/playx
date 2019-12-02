#include <painter_widget.h>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsView>
#include <cmath>

namespace playx::ui {

QSize painter_field::minimumSizeHint() const
{
    return QSize(720, 405);
}


painter_field::painter_field(QWidget *parent) :
    QWidget(parent)
{
    base_image = std::make_unique<QImage>(720, 405, QImage::Format::Format_A2BGR30_Premultiplied);
    layers.push_back(playx::core::layer(QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied), 0));

    for (auto &x : layers) {
        QPainter painter(base_image.get());
        painter.drawImage(QPoint(0, 0), x.get_image());
    }
}

void painter_field::createLayer(QImage image)
{
    layers.push_back(playx::core::layer(image, layers.size() - 1));
    currentLayerPos = layers.size() - 1;
    prevent_from_drawing = true;
    update();
}

void painter_field::setCurrentLayer(size_t pos)
{
    currentLayerPos = pos;
}

playx::core::layer& painter_field::getCurrentLayer()
{
    try {
        return layers.at(currentLayerPos);
    } catch (std::out_of_range& ex) {
        currentLayerPos = 0;
        return layers.at(currentLayerPos);
    }
}

void painter_field::drawBaseImage()
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), *base_image.get());
}

void painter_field::drawLayers()
{
    QPainter painter(base_image.get());
    base_image->fill(Qt::GlobalColor::transparent);
    for (auto &x : layers) {
        if (x.get_visibility_style()) {
            painter.drawImage(QPoint(0, 0), x.get_image());
        }
    }
    drawBaseImage();
}

void painter_field::interpolate(QPainter& p)
{
    double x = previous_point.x();
    double y = previous_point.y();
    auto const slope =
        static_cast<double>(point.y() - previous_point.y()) / (point.x() - previous_point.x());
    auto const intercept = y - slope * x;
    
    auto const x_diff = point.x() - previous_point.x();
    auto const y_diff = point.y() - previous_point.y();

    if (std::abs(x_diff) < 1 && std::abs(y_diff) > 1) {
        auto const y_unit = y_diff / std::abs(y_diff);
        for (int i = 0; std::abs(i) < std::abs(y_diff); i += y_unit) {
            p.drawEllipse(QPointF(point.x(), y + i), 4, 4);
        }
        return;
    } else if (std::abs(y_diff) < 1 && std::abs(x_diff) > 1) {
        auto const x_unit = x_diff / std::abs(x_diff);
        for (int i = 0; std::abs(i) < std::abs(x_diff); i += x_unit) {
            p.drawEllipse(QPointF(x + i, point.y()), 4, 4);
        }
        return;
    } else if (std::abs(x_diff) < 1 || std::abs(y_diff) < 1) {
        // nothing to do.
        return;
    } else {
        auto const x_unit = x_diff / std::abs(x_diff);
        auto const y_unit = y_diff / std::abs(y_diff);
        auto const is_x_diff_longer_than_y_diff = std::abs(x_diff) > std::abs(y_diff);
        if (is_x_diff_longer_than_y_diff) {
            for (int i = 0; std::abs(i) < std::abs(x_diff); i += x_unit) {
                p.drawEllipse(QPointF(x + i, slope * (x + i) + intercept), 4, 4);
            }
        } else {
             for (int i = 0; std::abs(i) < std::abs(y_diff); i += y_unit) {
                p.drawEllipse(QPointF(((y + i) - intercept) / slope, y + i), 4, 4);
            }
        }
    }
}

void painter_field::paintEvent(QPaintEvent*)
{
    if (prevent_from_drawing) {
        drawLayers();
        return;
    }
    auto& image = getCurrentLayer().get_image();
    QPainter p(&image);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 0, 0));
    interpolate(p);
    p.drawEllipse(point, 4, 4);
    p.end();
    drawLayers();
}
void painter_field::mouseMoveEvent(QMouseEvent *event)
{
    previous_point = point;
    point = event->pos();
    update();
}
void painter_field::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::MouseButton::LeftButton) {
        prevent_from_drawing = true;
    } else {
        prevent_from_drawing = false;
    }
    
    point = event->pos();
    previous_point = point;
}

}