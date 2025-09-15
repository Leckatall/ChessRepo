//
// Created by Lecka on 15/06/2025.
//

#include "repertoire_view.h"

#include "rep_move_card.h"
#include "ui/components/common/card_widget.h"

namespace repertoire_viewer {
    View::View(QWidget *parent)
        : QWidget(parent),
          m_moves_widget(new common::WidgetList(this)) {
        const auto layout = new QVBoxLayout();
        m_moves_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(m_moves_widget);
        setLayout(layout);
    }

    void View::updateMovesWidget(const QList<Models::Move>& moves) {
        m_moves_widget->clear_widgets();
        if (moves.isEmpty()) {
            m_moves_widget->add_widget(new QLabel("No Moves found for this FEN", m_moves_widget));
        }
        for(const auto& move: moves) {
            auto* move_card = new MoveCard(move, m_moves_widget);
            connect(move_card, &common::CardWidget::clicked, this, [this, move]{emit move_clicked(move);});
            m_moves_widget->add_widget(move_card);
        }
    }
}
