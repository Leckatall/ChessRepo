//
// Created by Lecka on 13/06/2025.
//

#include "moves_deck.h"

MovesDeck::MovesDeck(QWidget *parent)
    : QFrame(parent),
      m_scrollArea(new QScrollArea(this)),
      m_scroll_widget(new QWidget),
      m_scroll_layout(new QVBoxLayout(m_scroll_widget)) {
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_scroll_widget);

    m_scroll_layout->setAlignment(Qt::AlignTop);
    m_scroll_layout->setSpacing(8);

    const auto layout = new QVBoxLayout();
    //layout->setContentsMargins(0, 0, 0, 0);
    m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_scrollArea);
    setLayout(layout);
}

void MovesDeck::updateMoveCards(QList<MoveCard*> move_cards) {
    while (const QLayoutItem *item = m_scroll_layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    for(auto *card: move_cards) {
        m_scroll_layout->addWidget(card);
    }
}
