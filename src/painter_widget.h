#pragma once

#include<memory>
#include<QWidget>
#include<QtGui/QPainter>
#include<QMainWindow>
#include<QGraphicsView>
#include<QLabel>

namespace playx::ui {

class painter_field : public QWidget {

    Q_OBJECT
public:
    explicit painter_field(QWidget *parent = nullptr);
    ~painter_field();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint point;
    std::unique_ptr<QImage> image;
    std::unique_ptr<QLabel> target;
};

}