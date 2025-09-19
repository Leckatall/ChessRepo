//
// Created by Lecka on 19/09/2025.
//

#include "move_card.h"

#include <qboxlayout.h>

namespace View::Features::Repertoire {
    MoveCard::MoveCard(const QString &move, Domain::Types::PositionStats stats, QWidget *parent)
        : QFrame(parent),
          m_move_data(std::move(stats)),
          m_move_lbl(new QLabel(move, this)),
          m_move_stats(new StatsWidget(stats, this)) {
        QHBoxLayout layout{};
        layout.addWidget(m_move_lbl);
        layout.addWidget(m_move_stats);
        setLayout(&layout);
    }
}
