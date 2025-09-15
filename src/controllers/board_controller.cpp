
#include "board_controller.h"
#include "board_view.h"
#include "chess_primitives.h"

namespace chessboard {

Controller::Controller(QObject * parent)
        : QObject(parent),
          m_boardTblModel(this),
          m_boardProxyModel(this),
          m_view(new View()) {

        m_boardProxyModel.setSourceModel(&m_boardTblModel);
        m_view->setTblModel(&m_boardProxyModel);
        initConnections();
}

QString Controller::get_current_fen() const {

        return m_boardTblModel.get_fen();
}

void Controller::makeUciMove() {

        m_boardTblModel.makeUciMove(uci);
        m_boardTblModel.clear_selection();
}

void Controller::emitModelsFromUcis() {

        QList<Models::Move> moves = {};
        for(const auto move :uci_moves) {
            moves.append(m_boardTblModel.uci_to_model(move));
        }
        emit convertedUcis(moves);
}

// SIGNAL 0

void Controller::boardChanged(const Models::FEN & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void Controller::convertedUcis(QList<Models::Move> _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

void Controller::handleSquareClicked() {

        auto index = m_boardProxyModel.mapToSource(proxy_index);
        m_boardTblModel.begin_update();
        if (m_boardTblModel.square_selected()) {
            // A piece has already been selected
            m_boardTblModel.try_move_to(index);
            // Clear the current highlights:
            // Case A: they're moving, and they no longer apply
            // Case B: They're changing the piece to move, and they no longer apply
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

void Controller::flipBoard() {

        m_boardProxyModel.flip();
}

void Controller::undoMove() {

        m_boardTblModel.undo_move();
}

void Controller::initConnections() {

        connect(m_view, &View::square_clicked, this, &Controller::handleSquareClicked);
        connect(m_view, &View::undoMoveRequested, this, &Controller::undoMove);
        connect(m_view, &View::flipRequested,
                this, &Controller::flipBoard);
        connect(&m_boardTblModel, &TblModel::boardUpdated, this, &Controller::updateMoveHistory);
        connect(&m_boardTblModel, &TblModel::boardUpdated,
            this, [this]{emit boardChanged(Models::FEN(get_current_fen()));});
}


} // namespace chessboard
