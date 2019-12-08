#include "main_window.h"
#include "timeline_widget.h"
#include "application_state.h"

#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

#include <iostream>

namespace playx::ui {

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    setup();
}

void main_window::setup()
{
    app_state = std::make_shared<playx::core::application_state>(
        playx::core::timeline(playx::core::unit_frame(24)));
    window = std::make_unique<QWidget>();
    
    layout = std::make_unique<QGridLayout>();
    pf = std::make_unique<painter_field>();
    pf->set_application_state(app_state);

    auto tw = new timeline_widget;
    tw->set_application_state(app_state);
    connect(tw, SIGNAL (sendVisibilityChange()), pf.get(), SLOT (receiveChange()));

    layout->addWidget(pf.get(), 0, 0);

    sidebar_layout = std::make_unique<QVBoxLayout>();

    // buttons (temporary)
    auto button1 = new QPushButton("+layer");
    connect(button1, SIGNAL (released()), this, SLOT (handleButton1()));
    connect(button1, SIGNAL (released()), tw, SLOT (receiveLayerState()));

    button1->setFocusPolicy(Qt::NoFocus);
    sidebar_layout->addWidget(button1);

    auto button2 = new QPushButton("up");
    connect(button2, SIGNAL (released()), this, SLOT (handleButton2()));

    button2->setFocusPolicy(Qt::NoFocus);
    sidebar_layout->addWidget(button2);

    auto button3 = new QPushButton("down");
    connect(button3, SIGNAL (released()), this, SLOT (handleButton3()));
    
    button3->setFocusPolicy(Qt::NoFocus);
    sidebar_layout->addWidget(button3);

    layout->addLayout(sidebar_layout.get(), 0, 1);
    
    layout->addWidget(tw, 1,0);

    window->setLayout(layout.get());
    setCentralWidget(window.get());
}

void main_window::keyPressEvent(QKeyEvent *event)
{
    std::cout << "here" << std::endl;
    qDebug() << event->key();
    boost::bind(&painter_field::start_timer, pf.get())();
}

void main_window::handleButton1()
{
    auto image = QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied);
    image.fill(QColor(0, 0, 0, 80));
    pf->createLayer(image);
}

void main_window::handleButton2()
{
    std::cout << "called" << std::endl;
    app_state->change_current_layer_to(app_state->current_layer()->get_level() + 1);
}

void main_window::handleButton3()
{
    std::cout << "called" << std::endl;
    app_state->change_current_layer_to(app_state->current_layer()->get_level() - 1);
}

}