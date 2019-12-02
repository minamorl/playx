#include <main_window.h>
#include <QGridLayout>
#include <QPushButton>
#include <timeline_widget.h>

namespace playx::ui {

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    setup();
}

void main_window::setup()
{
    window = std::make_unique<QWidget>();
    
    layout = std::make_unique<QGridLayout>();
    pf = std::make_unique<painter_field>();
    layout->addWidget(pf.get(), 0, 0);

    sidebar_layout = std::make_unique<QVBoxLayout>();

    auto button1 = new QPushButton("+layer");
    connect(button1, SIGNAL (released()), this, SLOT (handleButton1()));
    sidebar_layout->addWidget(button1);

    auto button2 = new QPushButton("up");
    connect(button2, SIGNAL (released()), this, SLOT (handleButton2()));
    sidebar_layout->addWidget(button2);

    auto button3 = new QPushButton("down");
    connect(button3, SIGNAL (released()), this, SLOT (handleButton3()));
    sidebar_layout->addWidget(button3);

    layout->addLayout(sidebar_layout.get(), 0, 1);
    
    layout->addWidget(new timeline_widget, 1,0);

    window->setLayout(layout.get());
    setCentralWidget(window.get());
}

void main_window::handleButton1()
{
    auto image = QImage(720, 405, QImage::Format::Format_A2BGR30_Premultiplied);
    image.fill(QColor(0, 0, 0, 80));
    pf->createLayer(image);
}

void main_window::handleButton2()
{
    pf->setCurrentLayer(pf->currentLayerPos + 1);
}

void main_window::handleButton3()
{
    pf->setCurrentLayer(pf->currentLayerPos - 1);
}

}