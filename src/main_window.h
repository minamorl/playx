#pragma once

#include "application_state.h"
#include "layer.h"
#include "painter_widget.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QGridLayout>

#include <vector>
#include <memory>

namespace playx::ui {

class main_window : public QMainWindow {
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent* bar);

private slots:
    void handleButton1();
    void handleButton2();
    void handleButton3();


private:
    void setup();

    std::shared_ptr<playx::core::application_state> app_state;    
    std::unique_ptr<QWidget> window;
    std::unique_ptr<QGridLayout> layout;
    std::unique_ptr<QVBoxLayout> sidebar_layout;
    std::unique_ptr<painter_field> pf;
};

}