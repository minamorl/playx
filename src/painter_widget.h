#pragma once

#include<layer.h>
#include<memory>
#include<QWidget>
#include<QtGui/QPainter>
#include<QMainWindow>
#include<QGraphicsView>
#include<QLabel>
#include <application_state.h>

namespace playx::ui {

class painter_field : public QWidget {

    Q_OBJECT
public:
    explicit painter_field(QWidget *parent = nullptr);
    
    void set_application_state(std::shared_ptr<playx::core::application_state> app_state);
    void createLayer(QImage image);
    std::shared_ptr<playx::core::layer> getCurrentLayer();
    QSize minimumSizeHint() const;

signals:
    void changeLayerState();
public slots:
    void receiveChange();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void interpolate(QPainter& p);
    void drawLayers();
    void drawBaseImage();
    QPoint point_;
    QPoint previous_point_;
    std::unique_ptr<QImage> base_image_;
    std::vector<playx::core::layer> layers_;
    bool prevent_from_drawing_ = true;
    std::shared_ptr<playx::core::application_state> app_state_;
};

}