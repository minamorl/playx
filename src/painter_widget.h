#pragma once

#include<layer.h>
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
    void createLayer(QImage image);
    void setCurrentLayer(size_t pos);
    playx::core::layer& getCurrentLayer();
    size_t currentLayerPos = 0;
    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void interpolate(QPainter& p);
    void drawLayers();
    QPoint point;
    QPoint previous_point;
    std::unique_ptr<QImage> base_image;
    std::vector<playx::core::layer> layers;
    std::unique_ptr<QLabel> target;
    bool is_left_button_clicked = false;
};

}