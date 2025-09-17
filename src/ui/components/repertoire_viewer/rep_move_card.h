//
// Created by Lecka on 15/06/2025.
// Compatibility shim during refactor: use ui/components/move_card.h
//
#ifndef REP_MOVE_CARD_H
#define REP_MOVE_CARD_H

#include "ui/components/move_card.h"

namespace repertoire_viewer {
    // Deprecated alias to the canonical MoveCard widget
#if defined(_MSC_VER)
    using MoveCard = ::MoveCard; // __declspec(deprecated("Use ::MoveCard and include <ui/components/move_card.h>"))
#else
    using MoveCard = ::MoveCard; // [[deprecated("Use ::MoveCard and include <ui/components/move_card.h>")]]
#endif
}

#endif //REP_MOVE_CARD_H
