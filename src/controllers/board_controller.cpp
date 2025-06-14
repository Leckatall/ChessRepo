//
// Created by Lecka on 13/06/2025.
//

#include "board_controller.h"
#include "app/application.h"

namespace chessboard {
    Controller::Controller(QObject *parent)
        : QObject(parent),
          m_boardTblModel(this),
          m_boardProxyModel(this),
          m_view(new View()) {
        m_boardProxyModel.setSourceModel(&m_boardTblModel);
        m_view->setTblModel(&m_boardProxyModel);
        initConnections();
    }

    void Controller::initConnections() {
        connect(m_view, &View::square_clicked, this, &Controller::handleSquareClicked);
        connect(m_view, &View::undoMoveRequested, this, &Controller::undoMove);
        connect(m_view, &View::flipRequested,
                this, &Controller::flipBoard);
        connect(&m_boardTblModel, &TblModel::boardUpdated, this, &Controller::updateMoveHistory);
    }

    QString Controller::get_current_fen() const {
        return m_boardTblModel.get_fen();
    }

    void Controller::handleSquareClicked(const QModelIndex &proxy_index) {
        auto index = m_boardProxyModel.mapToSource(proxy_index);
        m_boardTblModel.begin_update();
        if (m_boardTblModel.square_selected()) {
            // A piece has already been selected
            m_boardTblModel.try_move_to(index);
            // Clear the currrent highlights:
            // Case A: they're moving and they no longer apply
            // Case B: They're changing the piece to move and they no longer apply
            m_boardTblModel.clear_selection();
        }
        m_boardTblModel.try_select(index);
        m_boardTblModel.end_update();
    }

    void Controller::updateMoveHistory() {
        QString pgn;
        int moveNumber = 1;
        const auto &moves = m_boardTblModel.get_history();
        for (int i = 0; i < moves.size(); i += 2) {
            pgn += QString("%1. %2%3  ").arg(moveNumber++)
                    .arg(moves[i].san)
                    .arg(i + 1 < moves.size() ? " " + moves[i + 1].san : "");
        }
        m_view->setHistoryLabel(pgn);
    }

    void Controller::makeUciMove(const QString &uci) {
        m_boardTblModel.makeUciMove(uci);
        m_boardTblModel.clear_selection();
    }

    void Controller::flipBoard() {
        m_boardProxyModel.flip();
    }

    void Controller::undoMove() {
        m_boardTblModel.undo_move();
        emit boardChanged(m_boardTblModel.get_fen());
    }
}
