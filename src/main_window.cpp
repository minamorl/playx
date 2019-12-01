#include <main_window.h>
#include <QHBoxLayout>

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
    window->setLayout(layout.get());
    setCentralWidget(window.get());
}

main_window::~main_window()
{
}

}