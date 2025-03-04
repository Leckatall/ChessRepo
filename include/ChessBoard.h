//
// Created by Lecka on 04/03/2025.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.hpp"

class ChessBoard : public chess::Board {
public:
    explicit ChessBoard();

    explicit ChessBoard(Board new_board);

    void show_moves_for_sq(chess::Square);

    chess::Movelist move_list;
private:


};


#endif //CHESSBOARD_H
