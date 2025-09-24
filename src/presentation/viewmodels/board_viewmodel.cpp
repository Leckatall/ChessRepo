//
// Created by Lecka on 19/09/2025.
//

#include "board_viewmodel.h"

namespace Presentation::Features::Board {
    BoardViewModel::BoardViewModel(Domain::Features::Chess::Board &board, QObject *parent)
        : QObject(parent),
          m_board(board),
          m_scene(View::Features::Board::BoardGraphicsScene(this)) {
        initConnections();
    }

    void BoardViewModel::updateScene() {
        QList<Domain::Types::Chess::PieceData> piece_data{};
        for (const auto &piece: m_board.getAllPieces()) {
            piece_data.append(piece);
        }
        m_scene.updateBoard(piece_data);
    }

    void BoardViewModel::undoMove() {
        m_board.undo_last_move();
    }

    void BoardViewModel::initConnections() {
        connect(&m_scene, &View::Features::Board::BoardGraphicsScene::squareClicked,
                this, &BoardViewModel::onSquareClicked);
    }

    void BoardViewModel::onSquareClicked(const Domain::Types::Chess::Square &square) {
        qDebug() << "BoardViewModel::onSquareClicked: " << square.file() << square.rank() << " id: " << square.m_id;
        if (m_board.is_enabled_square(square)) {
            qDebug() << "Selected square: " << square.file() << square.rank();
            m_scene.setSelectedSquare(new Domain::Types::Chess::Square(square));
            return;
        }
        if (Domain::Types::Chess::Square *selected_square = m_scene.selectedSquare(); selected_square) {
            if (m_board.get_legal_targets_from(*selected_square).contains(square)) {
                m_board.playMove({*selected_square, square});
                updateScene();
            }
        }
        m_scene.setSelectedSquare(nullptr);
    }

    void BoardViewModel::flipBoard() {
        m_white_on_bottom = !m_white_on_bottom;
    }
}
