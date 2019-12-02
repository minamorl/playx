#include <QWidget>
#include <QGridLayout>
#include <timeline_widget.h>
#include <memory>
#include <QMouseEvent>

namespace playx::ui {

timeline_cell::timeline_cell()
{
    setGeometry(0, 0, 15, 15);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(180, 180, 180));
    setAutoFillBackground(true);
    setPalette(pal);

    setFixedSize(15, 15);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void timeline_cell::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    switchBgColor();
}

void timeline_cell::switchBgColor()
{
   if (is_selected) {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(20, 20, 20));
        setPalette(pal);
   } else {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(180, 180, 180));
        setPalette(pal);
   }
   is_selected = !is_selected;
}

timeline_widget::timeline_widget() 
{
    layout = std::make_unique<QGridLayout>();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 20; j++) {
            layout->addWidget(new timeline_cell, i, j);
        }
    }
    setLayout(layout.get());
}

}