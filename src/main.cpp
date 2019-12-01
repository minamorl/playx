#include <QApplication>
#include <painter_widget.h>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    playx::ui::main_window window;
    window.show();
    return app.exec();
}