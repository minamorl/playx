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
    virtual ~main_window();
private:
    void setup();
    std::unique_ptr<main_window> ui;
};

}