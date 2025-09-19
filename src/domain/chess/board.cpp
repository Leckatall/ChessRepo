//
// Created by Lecka on 19/09/2025.
//

#include "board.h"
namespace Domain::Features::Chess {
    bool Board::playMove(const chess::Move &move) {
        const auto prev_state = getFen();
        makeMove(move);
        if (getFen() != prev_state) {
            update_legal_moves();
            return true;
        }
        return false;
    }

    std::vector<Types::Chess::Square> Board::get_legal_targets_from(const Types::Chess::Square &square) const {
        if (!is_enabled_square(square)) return {};
        return m_legal_moves.at(square);
    }

    bool Board::is_enabled_square(const Types::Chess::Square &square) const {
        return m_legal_moves.contains(square);
    }

    bool Board::undo_move(const chess::Move &m) {
        const auto prev_state = getFen();
        unmakeMove(m);
        if (getFen() != prev_state) {
            update_legal_moves();
            return true;
        }
        return false;
    }

    void Board::update_legal_moves() {
        m_legal_moves.clear();
        chess::Movelist moves;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::ALL>(moves, *this);
        for (auto move: moves) {
            m_legal_moves[move.from()].push_back(move.to());
        }
    }
}
