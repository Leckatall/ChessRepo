//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_MOVE_CARD_H
#define CHESSREPO_MOVE_CARD_H
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>

#include "ui/components/common/stats_painter.h"


namespace View::Features::Repertoire {
    class MoveCard : public QFrame {
        Q_OBJECT

    public:
        explicit MoveCard(const QString &move, Domain::Types::PositionStats stats, QWidget *parent = nullptr);

        signals:
            void clicked();

    private:
        // void initLayout();
        void mousePressEvent(QMouseEvent* event) override {
            if (event->button() == Qt::LeftButton)
                emit clicked();
        }
        Domain::Types::PositionStats m_move_data;
        bool m_recommended;

        QLabel* m_move_lbl;
        StatsWidget* m_move_stats;
    };
}



#endif //CHESSREPO_MOVE_CARD_H