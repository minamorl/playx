#include <painter_widget.h>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsView>
#include <cmath>

namespace playx::ui {

painter_field::painter_field(QWidget *parent) :
    QWidget(parent)
{
    image = std::make_unique<QImage>(720, 405, QImage::Format::Format_A2BGR30_Premultiplied);
    target = std::make_unique<QLabel>(this);
    target->setFixedSize(720, 405);
    target->setPixmap(QPixmap::fromImage(*image));
    target->show();
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
        for (int i = 0; std::abs(i) < std::abs(x_diff); i += x_unit) {
            const auto z = QPointF(x + i, slope * (x + i) + intercept);
            qDebug() << z;
            p.drawEllipse(QPointF(x + i, slope * (x + i) + intercept), 4, 4);
        }
    }
}

void painter_field::paintEvent(QPaintEvent*)
{
    QPainter p(image.get());
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0));
    interpolate(p);
    p.drawEllipse(point, 4, 4);
    p.end();
    target->setPixmap(QPixmap::fromImage(*image));
}
void painter_field::mouseMoveEvent(QMouseEvent *event)
{
    previous_point = point;
    point = event->pos();
    update();

    // qDebug() << point;
}

painter_field::~painter_field()
{}

}