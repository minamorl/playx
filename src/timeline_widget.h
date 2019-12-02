#pragma once

#include <QWidget>
#include <QGridLayout>
#include <memory>
#include <application_state.h>


namespace playx::ui {


class timeline_cell : public QWidget {

Q_OBJECT

public:
    timeline_cell();
    void set_application_state(std::shared_ptr<playx::core::application_state> app_state);
    void set_id(int id);
    void initialize();
signals:
    void notify_content_change();

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    void switchBgColor();
    bool is_selected = true;
    int _id;
    std::shared_ptr<playx::core::application_state> _app_state;
};

class timeline_widget : public QWidget {

Q_OBJECT

public:
    timeline_widget();
    void set_application_state(std::shared_ptr<playx::core::application_state> app_state);

signals:
    void sendVisibilityChange();
public slots:
    void receiveVisibilityChange();
    void receiveLayerState();
private:
    void render_widget();

    std::shared_ptr<playx::core::application_state> _app_state;
    std::vector<timeline_cell*> cells;
    std::unique_ptr<QGridLayout> layout;
};


}