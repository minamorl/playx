#include "painter_widget.h"
#include "unit_frame.h"
#include "keyframe.h"
#include "layer.h"

#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsView>

#include <iostream>
#include <cmath>

namespace playx::ui {

QSize painter_field::minimumSizeHint() const
{
    return QSize(720, 405);
}


painter_field::painter_field(QWidget *parent) :
    QWidget(parent)
{
    base_image_ = std::make_unique<QImage>(720, 405, QImage::Format::Format_A2BGR30_Premultiplied);
}

void painter_field::set_application_state(std::shared_ptr<playx::core::application_state> app_state)
{
    app_state_ = app_state;

    auto l = app_state->get_timeline().create_layer();
    app_state_->get_timeline().insert_keyframe(
        std::make_shared<playx::core::keyframe>(QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied), playx::core::unit_frame(0), playx::core::unit_frame(1)), l);
    // l.get_keyframe_container()->emplace_back(
    //     QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied), &l, playx::core::unit_frame(0), playx::core::unit_frame(1));
}


void painter_field::createLayer(QImage image)
{
    auto l = app_state_->get_timeline().create_layer();
    app_state_->change_current_layer_to(l->get_level());
    app_state_->get_timeline().insert_keyframe(
        std::make_shared<playx::core::keyframe>(image, playx::core::unit_frame(0), playx::core::unit_frame(1)), l);
    // l.get_keyframe_container()->emplace_back(
    //     image, &l, playx::core::unit_frame(0), playx::core::unit_frame(1));
    prevent_from_drawing_ = true;
    update();
}

std::shared_ptr<playx::core::layer> painter_field::getCurrentLayer()
{
    return app_state_->current_layer();
}

void painter_field::drawBaseImage()
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), *base_image_.get());
}

void painter_field::drawLayers()
{
    QPainter painter(base_image_.get());
    base_image_->fill(Qt::GlobalColor::transparent);
    for (auto &x : app_state_->get_timeline().get_all_layers()) {
        if (x->get_visibility_style()) {
            // painter.drawImage(QPoint(0, 0), x.get_keyframe_container()->get_keyframes().at(0).get_image());
            for (auto& y : app_state_->get_timeline().get_keyframes_at(playx::core::unit_frame(app_state_->get_current_frame()))) {
                if (y.first == x) {
                    painter.drawImage(QPoint(0, 0), y.second->get_image());
                }
            }
        }
    }
    drawBaseImage();
}

void painter_field::interpolate(QPainter& p)
{
    double x = previous_point_.x();
    double y = previous_point_.y();
    auto const slope =
        static_cast<double>(point_.y() - previous_point_.y()) / (point_.x() - previous_point_.x());
    auto const intercept = y - slope * x;
    
    auto const x_diff = point_.x() - previous_point_.x();
    auto const y_diff = point_.y() - previous_point_.y();

    if (std::abs(x_diff) < 1 && std::abs(y_diff) > 1) {
        auto const y_unit = y_diff / std::abs(y_diff);
        for (int i = 0; std::abs(i) < std::abs(y_diff); i += y_unit) {
            p.drawEllipse(QPointF(point_.x(), y + i), 4, 4);
        }
        return;
    } else if (std::abs(y_diff) < 1 && std::abs(x_diff) > 1) {
        auto const x_unit = x_diff / std::abs(x_diff);
        for (int i = 0; std::abs(i) < std::abs(x_diff); i += x_unit) {
            p.drawEllipse(QPointF(x + i, point_.y()), 4, 4);
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

void painter_field::receiveChange()
{
    update();
}

void painter_field::paintEvent(QPaintEvent*)
{
    if (prevent_from_drawing_) {
        drawLayers();
        return;
    }
    // auto& image = getCurrentLayer().get_keyframe_container()->get_keyframes().at(0).get_image();
    auto kfs = app_state_->get_timeline().get_keyframes_at(app_state_->get_current_frame());
    auto it = std::find_if(kfs.begin(), kfs.end(), [this](std::pair<std::shared_ptr<playx::core::layer>, std::shared_ptr<playx::core::keyframe>> x) { return x.first == getCurrentLayer(); });
    if (it == kfs.end()) {
        std::cout << "not found" << std::endl;
        return;
    }
    auto& image = it->second->get_image();
    QPainter p(&image);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 0, 0));
    interpolate(p);
    p.drawEllipse(point_, 4, 4);
    p.end();
    drawLayers();
}
void painter_field::mouseMoveEvent(QMouseEvent *event)
{
    previous_point_ = point_;
    point_ = event->pos();
    update();
}
void painter_field::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::MouseButton::LeftButton) {
        prevent_from_drawing_ = true;
    } else {
        prevent_from_drawing_ = false;
    }
    point_ = event->pos();
    previous_point_ = point_;
}

}