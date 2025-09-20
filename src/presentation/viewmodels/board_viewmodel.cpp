//
// Created by Lecka on 19/09/2025.
//

#include "board_viewmodel.h"

namespace Presentation::Features::Board {
    BoardViewModel::BoardViewModel(Domain::Features::Chess::Board& board, QObject *parent)
        : QObject(parent), m_board(board){
    }

    QPointF BoardViewModel::squareToPoint(const Domain::Types::Chess::Square &square) const {
        const int xpos = square.file() * m_square_size;
        const int ypos = (m_white_on_bottom ? 8 - square.rank() : square.rank() - 1) * m_square_size;
        return QPointF(xpos, ypos);
    }

    QRectF BoardViewModel::squareToRect(const Domain::Types::Chess::Square &square) const {
        QPointF top_left = squareToPoint(square);
        return QRectF(top_left, QSizeF(m_square_size, m_square_size));
    }

    Domain::Types::Chess::Square BoardViewModel::pointToSquare(const QPointF &point) const {
        const int file = static_cast<int>(point.x() / m_square_size);
        const int rank = 8 - static_cast<int>(point.y() / m_square_size);
        return Domain::Types::Chess::Square(file, rank);
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
