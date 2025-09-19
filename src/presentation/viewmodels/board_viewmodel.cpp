//
// Created by Lecka on 19/09/2025.
//

#include "board_viewmodel.h"

namespace Presentation::Features::Board {
    BoardViewModel::BoardViewModel(Domain::Features::Chess::Board& board, QObject *parent)
        : QObject(parent), m_board(board){
    }

    void BoardViewModel::makeMove(const Domain::Types::Chess::Move &move) {
        if (m_board.playMove(move)) refresh();
    }

    void BoardViewModel::undoMove() {
        m_board.undo_last_move();
    }

    void BoardViewModel::onSquareClicked(const Domain::Types::Chess::Square square) {

    }

    void BoardViewModel::flipBoard() {
        m_white_on_bottom = !m_white_on_bottom;
    }


}
