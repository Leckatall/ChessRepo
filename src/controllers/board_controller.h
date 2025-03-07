//
// Created by Lecka on 05/03/2025.
//

#ifndef CHESS_BOARD_CONTROLLER_H
#define CHESS_BOARD_CONTROLLER_H

#include "models/board_model.h"


class BoardController : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString BLACK_SQUARE READ BLACK_SQUARE NOTIFY accessedConstant)

    Q_PROPERTY(QString WHITE_SQUARE READ WHITE_SQUARE NOTIFY accessedConstant)

public:
    explicit BoardController(QObject *parent = nullptr): board(BoardModel()) {
    }

    Q_INVOKABLE [[nodiscard]] static QString WHITE_SQUARE() { return "#646464"; }
    Q_INVOKABLE [[nodiscard]] static QString BLACK_SQUARE() { return "#000000"; }
    Q_INVOKABLE void make_move();

    Q_INVOKABLE void undo_move();

    Q_INVOKABLE void redo_move();

    Q_INVOKABLE void update_view();

signals:
    void accessedConstant();

private:
    BoardModel board;
    int selected_square = 64;
};


#endif //CHESS_BOARD_CONTROLLER_H
