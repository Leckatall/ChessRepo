//
// Created by Lecka on 13/06/2025.
//

#include "move_card.h"

#include <qboxlayout.h>
#include <utility>


MoveCard::MoveCard(Models::MoveData move_data, const bool recommended, QWidget *parent)
    : common::CardWidget(m_move_data.move.san, parent),
      m_move_data(std::move(move_data)),
      m_recommended(recommended),
      m_move_lbl(new QLabel(m_move_data.move.san, this)),
      m_move_stats(new StatsWidget(m_move_data.position_data, this)) {
    auto* layout = new QHBoxLayout();
    layout->addWidget(m_move_lbl);
    layout->addWidget(m_move_stats);
    setLayout(layout);
}

MoveCard::MoveCard(const Models::Move &move, QWidget *parent)
    : MoveCard(Models::MoveData{move, Models::PositionStats{}}, false, parent) {}
