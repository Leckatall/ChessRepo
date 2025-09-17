//
// Created by Lecka on 13/06/2025.
//

#ifndef MOVE_CARD_H
#define MOVE_CARD_H
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>

#include "ui/components/common/card_widget.h"
#include "common/stats_painter.h"
#include "models/datatypes/move.h"


class MoveCard : public common::CardWidget {
    Q_OBJECT

public:
    explicit MoveCard(Models::MoveData move_data, bool recommended, QWidget *parent = nullptr);
    // Compatibility ctor for legacy call sites using Models::Move
    explicit MoveCard(const Models::Move& move, QWidget *parent = nullptr);

private:
    void initLayout();
    Models::MoveData m_move_data;
    bool m_recommended;

    QLabel* m_move_lbl;
    StatsWidget* m_move_stats;
};


#endif //MOVE_CARD_H
