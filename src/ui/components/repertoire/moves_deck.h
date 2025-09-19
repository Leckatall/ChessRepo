//
// Created by Lecka on 13/06/2025.
//

#ifndef MOVES_DECK_H
#define MOVES_DECK_H
#include <qboxlayout.h>
#include <QScrollArea>

#include "ui/components/move_card.h"

namespace View::Feature::Repertoire {
    class MovesDeck : public QFrame {
        Q_OBJECT

    public:
        explicit MovesDeck(QWidget *parent = nullptr);

        void updateMoveCards(QList<MoveCard *> move_cards);

    private:
        QScrollArea *m_scrollArea;
        QWidget *m_scroll_widget;
        QVBoxLayout *m_scroll_layout;
    };
}


#endif //MOVES_DECK_H
