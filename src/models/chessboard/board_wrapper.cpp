//
// Created by Lecka on 07/03/2025.
//

#include "board_wrapper.h"

namespace chessboard {
    // Move methods
    bool Board::make_move(const chess::Move m) {
        auto prev_state = fen();
        makeMove(m);
        if(fen() == prev_state) {
            return false;
        }
        m_move_history.append(moveModel(m));
        return true;
    }

    bool Board::undo_last_move() {
        if (m_move_history.isEmpty()) { return false; }
        return undo_move(m_move_history.takeLast());
    }

    bool Board::undo_move(const Models::Move &m) {
        auto prev_state = fen();
        unmakeMove(move(m));
        return fen() != prev_state;
    }

    QSet<chess::Square> Board::get_legal_targets_for(const chess::Square &square) const {
        QSet<chess::Square> targets = {};
        chess::Movelist moves;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::ALL>(moves, *this);
        for (auto move: moves) {
            if (move.from() == square) {
                targets << move.to();
            }
        }
        return targets;
    }

    /**
     *
     * @param square
     * @return is there a piece of the color to move at this square
     */
    bool Board::is_enabled_square(const chess::Square &square) const {
        const chess::Piece piece = at(square);
        if (piece == chess::Piece::NONE) {
            return false;
        }
        if (piece.color() != sideToMove()) {
            return false;
        }
        return true;
    }


}
