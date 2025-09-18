//
// Created by Lecka on 18/09/2025.
//

#ifndef CHESSREPO_CHESS_H
#define CHESSREPO_CHESS_H
#include "chess.hpp"
#include "domain/types/fen.h"
#include "domain/types/uci_move.h"

namespace Utils::Chess {
    inline Domain::Types::FEN resultOfMove(const Domain::Types::FEN &fen, const Domain::Types::UCIMove &move) {
        chess::Board board(fen);
        board.makeMove(chess::uci::uciToMove(board, move));
        return Domain::Types::FEN(board.getFen());
    }
}
#endif //CHESSREPO_CHESS_H
