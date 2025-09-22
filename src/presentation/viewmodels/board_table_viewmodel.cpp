//
// Created by Lecka on 22/09/2025.
//

#include "board_table_viewmodel.h"

namespace Presentation::Features::Board {
    BoardTableViewModel::BoardTableViewModel(Domain::Features::Chess::Board &board, QObject *parent)
        : QObject(parent),
          m_board(board),
          m_boardTblModel(this),
          m_boardProxyModel(this) {
        m_boardProxyModel.setSourceModel(&m_boardTblModel);
        initConnections();
    }

    QString BoardTableViewModel::get_current_fen() const {
        return m_boardTblModel.get_fen();
    }

    void BoardTableViewModel::makeUciMove(const Domain::Types::UCIMove &uci) {
        // TODO use m_board instead omg
        m_boardTblModel.makeUciMove(uci);
        m_boardTblModel.clear_selection();
        emit boardChanged(m_boardTblModel.get_fen().toStdString());
    }

    void BoardTableViewModel::handleSquareClicked(const QModelIndex &proxy_index) {
        const auto index = m_boardProxyModel.mapToSource(proxy_index);
        m_boardTblModel.begin_update();
        if (m_boardTblModel.square_selected()) {
            // A piece has already been selected
            m_boardTblModel.try_move_to(index);
            // Clear the current highlights:
            // Case A: they're moving, and they no longer apply
            // Case B: They're changing the piece to move and they no longer apply
            m_boardTblModel.clear_selection();
            emit boardChanged(m_boardTblModel.get_fen().toStdString());
        }
        m_boardTblModel.try_select(index);
        m_boardTblModel.end_update();
    }

    void BoardTableViewModel::updateMoveHistory() {
        QString pgn;
        int moveNumber = 1;
        const auto &moves = m_boardTblModel.get_history();
        for (int i = 0; i < moves.size(); i += 2) {
            pgn += QString("%1. %2%3  ").arg(moveNumber++)
                    .arg(moves[i].san)
                    .arg(i + 1 < moves.size() ? " " + moves[i + 1].san : "");
        }
        emit boardHistoryChanged(pgn);
    }

    void BoardTableViewModel::flipBoard() {
        m_boardProxyModel.flip();
    }

    void BoardTableViewModel::undoMove() {
        m_boardTblModel.undo_move();
        emit boardChanged(m_boardTblModel.get_fen().toStdString());
    }

    void BoardTableViewModel::initConnections() {
        connect(&m_boardTblModel, &chessboard::TblModel::boardUpdated,
                this, &BoardTableViewModel::updateMoveHistory);
    }
}
