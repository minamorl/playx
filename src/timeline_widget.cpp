#include "application_state.h"
#include "timeline_widget.h"

#include <QWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QDebug>

#include <memory>
#include <iostream>

namespace playx::ui {

timeline_cell::timeline_cell(QWidget* parent) : QWidget(parent)
{
    setGeometry(0, 0, 15, 15);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(180, 180, 180));
    setAutoFillBackground(true);
    setPalette(pal);

    setFixedSize(15, 15);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void timeline_cell::set_application_state(std::shared_ptr<playx::core::application_state> app_state)
{
    app_state_ = app_state;
}

void timeline_cell::set_index(uint layer_idx, playx::core::unit_frame keyframe_idx)
{
    layer_idx_ = layer_idx;
    keyframe_idx_ = keyframe_idx;
}
 

void timeline_cell::initialize()
{
    auto component = app_state_->get_timeline().find_component(layer_idx_, keyframe_idx_);
    if (component == boost::none) {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(230, 230, 230));
        setPalette(pal);
        return;
    }
    auto visibility = component->first->get_visibility_style();
    if (visibility) {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(20, 20, 20));
        setPalette(pal);
   } else {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(180, 180, 180));
        setPalette(pal);
   }
   is_selected_ = visibility;
}

void timeline_cell::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event;
    if (event->button() != Qt::LeftButton) {
        return;
    }
    auto component = app_state_->get_timeline().find_or_create_component(layer_idx_, keyframe_idx_, keyframe_idx_ + playx::core::unit_frame(1));
    app_state_->set_current_frame(keyframe_idx_);

    switchBgColor();
    component.first->set_visibility_style(is_selected_);

    notify_content_change();
}

void timeline_cell::switchBgColor()
{
    is_selected_ = !is_selected_;

    if (is_selected_) {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(20, 20, 20));
        setPalette(pal);
    } else {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(180, 180, 180));
        setPalette(pal);
    }
}

timeline_widget::timeline_widget() 
{}

void timeline_widget::set_application_state(std::shared_ptr<playx::core::application_state> app_state)
{
    app_state_ = app_state;
    render_widget();
}

void timeline_widget::render_widget()
{
    layout_ = std::make_unique<QGridLayout>();
    for (uint i = 0; i < app_state_->get_timeline().get_all_layers().size(); i++) {
        for (uint j = 0; j < app_state_->get_timeline().get_length().get_index(); j++) { 
            auto c = new timeline_cell();
            c->set_application_state(app_state_);
            c->set_index(i, playx::core::unit_frame(j));
            c->initialize();
            cells_.push_back(c);
            layout_->addWidget(c, app_state_->get_timeline().get_all_layers().size() - i, j);
            connect(c, SIGNAL(notify_content_change()), this, SLOT(receiveVisibilityChange()));
        }
    }
    setLayout(layout_.get());
}

void timeline_widget::receiveLayerState()
{
    std::cout << "received" << std::endl;
    render_widget();
}

void timeline_widget::receiveVisibilityChange()
{
    sendVisibilityChange();
}


}