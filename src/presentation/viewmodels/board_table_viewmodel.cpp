//
// Created by Lecka on 22/09/2025.
//

#include "board_table_viewmodel.h"

namespace Presentation::Features::Board {
    BoardTableViewModel::BoardTableViewModel(Domain::Features::Chess::Board &board, QObject *parent)
        : QObject(parent),
          m_board(board),
          m_boardTblModel(m_board, this),
          m_boardProxyModel(this) {
        m_boardProxyModel.setSourceModel(&m_boardTblModel);
        initConnections();
    }

    void BoardTableViewModel::makeUciMove(const Domain::Types::UCIMove &uci) {
        if (m_board.playMove(uci)) {
            m_boardTblModel.clear_selection();
            emit boardChanged(m_board.fen());
        }
    }

    void BoardTableViewModel::handleSquareClicked(const QModelIndex &proxy_index) {
        const auto index = m_boardProxyModel.mapToSource(proxy_index);
        m_boardTblModel.begin_update();
        // Has a piece already been selected?
        if (m_boardTblModel.square_selected()) {
            const chess::Square source = m_boardTblModel.index_to_square(m_boardTblModel.get_selected_square());
            const chess::Square target = m_boardTblModel.index_to_square(index);
            makeUciMove(chess::uci::moveToUci(chess::Move::make(source, target)));
        }
        m_boardTblModel.try_select(index);
        m_boardTblModel.end_update();
    }


    void BoardTableViewModel::flipBoard() {
        m_boardProxyModel.flip();
    }

    void BoardTableViewModel::undoMove() {
        m_board.undo_last_move();
        emit boardChanged(m_board.fen());
    }

    void BoardTableViewModel::initConnections() {
        // TODO: See what slots need patching
        // connect(&m_boardTblModel, &chessboard::TblModel::boardUpdated,
        //         this, &BoardTableViewModel::updateMoveHistory);
    }
}
