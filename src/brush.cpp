#include "brush.h"

namespace playx::tools {

void brush::paint(QPointF point) {
    p_.drawEllipse(point, size_, size_);
}

}