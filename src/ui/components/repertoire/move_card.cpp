//
// Created by Lecka on 19/09/2025.
//

#include "move_card.h"

#include <qboxlayout.h>

namespace View::Features::Repertoire {
    MoveCard::MoveCard(Domain::Types::MoveData move_data, QWidget *parent)
        : QFrame(parent),
          m_move_data(move_data),
          m_move_lbl(new QLabel(QString::fromStdString(move_data.uci), this)),
          m_move_stats(new StatsWidget(move_data.stats, this)),
          m_layout(new QHBoxLayout(this)) {
        setFrameStyle(StyledPanel);
        m_layout->addWidget(m_move_lbl);
        m_layout->addWidget(m_move_stats);
        setLayout(m_layout);
    }
}
