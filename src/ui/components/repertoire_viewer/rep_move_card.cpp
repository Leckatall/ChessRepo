//
// Created by Lecka on 15/06/2025.
//

#include "rep_move_card.h"

#include <utility>

namespace repertoire_viewer {
    MoveCard::MoveCard(Models::Move move, QWidget *parent)
        : m_move(std::move(move)),
          CardWidget(m_move.san, parent) {
    }
}
