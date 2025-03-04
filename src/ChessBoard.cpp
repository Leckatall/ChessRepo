//
// Created by Lecka on 04/03/2025.
//

#include "ChessBoard.h"

#include <utility>

ChessBoard::ChessBoard(): move_list(chess::Movelist()) {}

ChessBoard::ChessBoard(Board new_board): Board(std::move(new_board)), move_list(chess::Movelist()) {}


