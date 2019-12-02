#pragma once

#include <QWidget>
#include <QGridLayout>
#include <memory>

namespace playx::ui {


class timeline_cell : public QWidget {

Q_OBJECT

public:
    timeline_cell();
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    void switchBgColor();
    bool is_selected = false;
};

class timeline_widget : public QWidget {

Q_OBJECT

public:
    timeline_widget();
private:
    std::unique_ptr<QGridLayout> layout;
};


}