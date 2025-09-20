//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_MOVE_CARD_H
#define CHESSREPO_MOVE_CARD_H
#include <qboxlayout.h>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>

#include "types/collections.h"
#include "ui/components/common/stats_painter.h"


namespace View::Features::Repertoire {
    class MoveCard : public QFrame {
        Q_OBJECT

    public:
        explicit MoveCard(Domain::Types::MoveData move_data, QWidget *parent = nullptr);

        signals:
            void clicked(Domain::Types::UCIMove move);

    private:
        // void initLayout();
        void mousePressEvent(QMouseEvent* event) override {
            if (event->button() == Qt::LeftButton)
                emit clicked(m_move_data.uci);
        }
        Domain::Types::MoveData m_move_data;
        bool m_recommended;

        QLabel* m_move_lbl;
        StatsWidget* m_move_stats;
        QHBoxLayout* m_layout;
    };
}



#endif //CHESSREPO_MOVE_CARD_H