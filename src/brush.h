#pragma once

#include <QPainter>

namespace playx::tools {

class brush {
public:
    brush(QPainter& p, int size) : p_(p), size_(size) {
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(255, 0, 0));
    }
    void paint(QPointF point);

private:
    QPainter& p_;
    int size_;
};

}