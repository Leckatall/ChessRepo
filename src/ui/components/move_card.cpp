
#include "move_card.h"
#include "stats_painter.h"

// SIGNAL 0

void MoveCard::clicked() {

    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

