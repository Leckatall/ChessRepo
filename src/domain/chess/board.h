//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_BOARD_H
#define CHESSREPO_BOARD_H
#include <stack>

#include "chess.hpp"
#include "primitives.h"
#include "domain/types/fen.h"
#include "domain/types/uci_move.h"

namespace Domain::Features::Chess {
    class Board : chess::Board {
    public:
        Board() = default;

        explicit Board(const chess::Board &new_board) : chess::Board(new_board) {
        }

        bool playMove(const chess::Move &move);
        bool playMove(const Types::UCIMove &move) { return playMove(chess::uci::uciToMove(*this, move));}
        bool playMove(const Types::Chess::Move &move) {return playMove(move.toChessLib());}
        bool playMove(const Types::Chess::Square &from, const Types::Chess::Square &to) { return playMove({from, to});}

        Types::FEN fen() const { return getFen(); }
        void set_fen(const Types::FEN &fen) { setFen(fen);}

        [[nodiscard]] std::vector<Types::Chess::Square>
        get_legal_targets_from(const Types::Chess::Square &square) const;

        [[nodiscard]] bool is_enabled_square(const Types::Chess::Square &square) const;

        // New Functionality
        std::stack<chess::Move> get_history() { return m_move_stack; }

        bool undo_last_move() {if (m_move_stack.empty()) { return false; } return undo_move(m_move_stack.top());}

    private:
        // Move history must be stored in ches slib format as the same Move object can only undo itself
        bool undo_move(const chess::Move &m);
        void update_legal_moves();

        std::stack<chess::Move> m_move_stack{};
        std::unordered_map<Types::Chess::Square, std::vector<Types::Chess::Square>> m_legal_moves{};
    };
}


#endif //CHESSREPO_BOARD_H
