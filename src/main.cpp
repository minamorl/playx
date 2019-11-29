#include <QApplication>
#include <QLabel>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QLabel* label = new QLabel("This is the beginning of domination.");
    label->resize(240, 120);
    label->show();
    return app.exec();
}