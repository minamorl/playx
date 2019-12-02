#pragma once

#include <painter_widget.h>

#include <memory>
#include <QMainWindow>
#include <QHBoxLayout>

namespace playx::ui {

class main_window : public QMainWindow {
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);

private slots:
    void handleButton1();
    void handleButton2();
    void handleButton3();


private:
    void setup();
    std::unique_ptr<QWidget> window;
    std::unique_ptr<QHBoxLayout> layout;
    std::unique_ptr<QVBoxLayout> sidebar_layout;
    std::unique_ptr<painter_field> pf;
};

}