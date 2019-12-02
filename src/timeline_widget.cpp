#include <QWidget>
#include <QGridLayout>
#include <timeline_widget.h>
#include <memory>
#include <QMouseEvent>
#include <iostream>
#include <application_state.h>
#include <QDebug>

namespace playx::ui {

timeline_cell::timeline_cell()
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
    _app_state = app_state;
}

void timeline_cell::set_id(int id)
{
    _id = id;
}

void timeline_cell::initialize()
{
    auto const visibility = _app_state->get_layer_container().at(_id).get_visibility_style();
    if (visibility) {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(20, 20, 20));
        setPalette(pal);
   } else {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(180, 180, 180));
        setPalette(pal);
   }
   is_selected = visibility;
}

void timeline_cell::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event;
    if (event->button() != Qt::LeftButton) {
        return;
    }
    switchBgColor();
    _app_state->get_layer_container().at(_id).set_visibility_style(is_selected);

    notify_content_change();
}

void timeline_cell::switchBgColor()
{
    is_selected = !is_selected;

    if (is_selected) {
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
    _app_state = app_state;
    render_widget();
}

void timeline_widget::render_widget()
{
    layout = std::make_unique<QGridLayout>();
    for (uint32_t i = 0; i < _app_state->get_layer_container().size(); i++) {
        auto c = new timeline_cell();
        c->set_application_state(_app_state);
        c->set_id(i);
        c->initialize();
        cells.push_back(c);
        layout->addWidget(c, i, 0);
        connect(c, SIGNAL(notify_content_change()), this, SLOT(receiveVisibilityChange()));
    }
    setLayout(layout.get());
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