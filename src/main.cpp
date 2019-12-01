#include <QApplication>
#include <main_window.h>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    playx::ui::main_window window;
    window.show();
    app.exec();
}