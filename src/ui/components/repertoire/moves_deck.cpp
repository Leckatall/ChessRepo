//
// Created by Lecka on 13/06/2025.
//

#include "moves_deck.h"

#include "types/collections.h"
#include "types/uci_move.h"

namespace View::Features::Repertoire {
    MovesDeck::MovesDeck(QWidget *parent)
        : QFrame(parent),
          m_scrollArea(new QScrollArea(this)),
          m_scroll_widget(new QWidget(m_scrollArea)),
          m_scroll_layout(new QVBoxLayout(m_scroll_widget)) {
        m_scrollArea->setWidgetResizable(true);
        m_scrollArea->setWidget(m_scroll_widget);

        m_scroll_layout->setAlignment(Qt::AlignTop);
        m_scroll_layout->setSpacing(8);

        auto layout = new QVBoxLayout(this);
        //layout->setContentsMargins(0, 0, 0, 0);
        m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(m_scrollArea);
        setLayout(layout);
    }

    void MovesDeck::setMoves(QList<Domain::Types::MoveData> moves) {
        while (QLayoutItem *item = m_scroll_layout->takeAt(0)) {
            delete item->widget();
            delete item;
        }
        m_move_cards.clear();
        m_move_cards.reserve(moves.size());
        for (const auto &move: moves) {
            auto *card = new MoveCard(move,this);
            m_move_cards.append(card);
            card->setFixedHeight(50);
            m_scroll_layout->addWidget(card);
            connect(card, &MoveCard::clicked,
                    this, [this](const Domain::Types::MoveData &move_data) { emit moveClicked(move_data); });
        }
    }
}
