//
// Created by Lecka on 13/06/2025.
//

#ifndef MOVE_CARD_H
#define MOVE_CARD_H
#include <QLabel>
#include <QMouseEvent>

#include "common/stats_painter.h"
#include "models/datatypes.h"


class MoveCard : public QFrame {
    Q_OBJECT

public:
    explicit MoveCard(Models::MoveData move_data, bool recommended, QWidget *parent = nullptr);

signals:
    void clicked();

private:
    // void initLayout();
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton)
            emit clicked();
    }
    Models::MoveData m_move_data;
    bool m_recommended;

    QLabel* m_move_lbl;
    StatsWidget* m_move_stats;
};


#endif //MOVE_CARD_H
