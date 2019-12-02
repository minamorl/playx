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
    images.push_back(QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied));

    for (auto const &x : images) {
        auto pixmap = QPixmap::fromImage(x);
        QPainter painter(base_image.get());
        painter.drawImage(QPoint(0, 0), x);
    }

    target = std::make_unique<QLabel>(this);
    target->setFixedSize(720, 405);
    target->setPixmap(QPixmap::fromImage(*base_image.get()));
    target->show();
}

void painter_field::createLayer(QImage image)
{
    images.push_back(image);
    currentLayerPos = images.size() - 1;
}

void painter_field::setCurrentLayer(size_t pos)
{
    currentLayerPos = pos;
}

QImage& painter_field::getCurrentLayer()
{
    try {
        return images.at(currentLayerPos);
    } catch (std::out_of_range& ex) {
        currentLayerPos = 0;
        return images.at(currentLayerPos);
    }
}

void painter_field::drawLayers()
{
    QPainter painter(base_image.get());
    base_image->fill(Qt::GlobalColor::transparent);
    for (auto const &x : images) {
        auto pixmap = QPixmap::fromImage(x);
        painter.drawImage(QPoint(0, 0), x);
    }
    target->setPixmap(QPixmap::fromImage(*base_image.get()));
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
    if (!is_left_button_clicked) {
        return;
    }
    auto& currentLayer = getCurrentLayer();
    QPainter p(&currentLayer);
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
    is_left_button_clicked = event->button() == Qt::MouseButton::LeftButton;
    point = event->pos();
    previous_point = point;
}

}