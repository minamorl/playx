#pragma once

#include<QWidget>
#include<QtGui/QPainter>
#include<QMainWindow>

namespace playx::ui {
class main_window : public QMainWindow {
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    virtual ~main_window();
private:
    main_window *ui;
};
};