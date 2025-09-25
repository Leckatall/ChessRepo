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
    inline std::vector<Domain::Types::UCIMove> legalMovesFromFen(const Domain::Types::FEN &fen) {
        const chess::Board board(fen);
        chess::Movelist move_list;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::ALL>(move_list, board);
        std::vector<Domain::Types::UCIMove> moves;
        moves.reserve(move_list.size());
        for (const auto &move: move_list) {
            moves.push_back(chess::uci::moveToUci(move));
        }
        return moves;
    }
}
#endif //CHESSREPO_CHESS_H
