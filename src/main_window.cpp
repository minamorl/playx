#include <main_window.h>
#include <QHBoxLayout>
#include <QPushButton>

namespace playx::ui {

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    setup();
}

void main_window::setup()
{
    window = std::make_unique<QWidget>();
    layout = std::make_unique<QHBoxLayout>();
    pf = std::make_unique<painter_field>();
    layout->addWidget(pf.get());
    
    auto button1 = new QPushButton("+layer");
    connect(button1, SIGNAL (released()), this, SLOT (handleButton1()));
    layout->addWidget(button1);

    auto button2 = new QPushButton("up");
    connect(button2, SIGNAL (released()), this, SLOT (handleButton2()));
    layout->addWidget(button2);

    auto button3 = new QPushButton("down");
    connect(button3, SIGNAL (released()), this, SLOT (handleButton3()));
    layout->addWidget(button3);

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