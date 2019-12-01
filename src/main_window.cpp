#include <main_window.h>
#include <QHBoxLayout>

namespace playx::ui {

main_window::main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(this)
{
    setup();
}

void main_window::setup()
{
    auto window = new QWidget;
    auto layout = new QHBoxLayout;
    layout->addWidget(new painter_field);
    window->setLayout(layout);
    setCentralWidget(window);
}

main_window::~main_window()
{
}

}