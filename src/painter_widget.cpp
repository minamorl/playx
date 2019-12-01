#include <painter_widget.h>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsView>

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

void painter_field::paintEvent(QPaintEvent*)
{
    QPainter p(image.get());
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0));
    p.drawEllipse(point, 4, 4);
    p.end();
    target->setPixmap(QPixmap::fromImage(*image));
}
void painter_field::mouseMoveEvent(QMouseEvent *event)
{
    point = event->pos();
    update();

    // qDebug() << point;
}

painter_field::~painter_field()
{}

}