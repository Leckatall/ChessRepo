//
// Created by Lecka on 15/06/2025.
//

#ifndef REP_MOVE_CARD_H
#define REP_MOVE_CARD_H
#include "models/datatypes.h"
#include "ui/components/common/card_widget.h"
#include "ui/components/common/stats_painter.h"


namespace repertoire_viewer {
    class MoveCard: public common::CardWidget {
        Q_OBJECT
    public:
        explicit MoveCard(Models::Move move, QWidget *parent=nullptr);

    private:
        Models::Move m_move;
        // StatsWidget* m_stats_widget;
    };
}




#endif //REP_MOVE_CARD_H
