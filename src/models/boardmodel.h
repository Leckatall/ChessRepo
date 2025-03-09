//
// Created by Lecka on 08/03/2025.
//

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include <chess.hpp>
#include <QObject>
#include <qset.h>

#include "squaremodel.h"
#include "views/boardview.h"


class BoardModel: public QObject{
    Q_OBJECT
public:
    std::array<SquareModel, 64> state();
    void make_move();
    void undo_move();

    SquareModel square(chess::Square);

private:
    chess::Board m_board_db;
    SquareModel* m_selected_square = {};
    QSet<SquareModel*> m_targeted_squares;
};



#endif //BOARDMODEL_H
