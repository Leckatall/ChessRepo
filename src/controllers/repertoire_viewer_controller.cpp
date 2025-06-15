//
// Created by Lecka on 15/06/2025.
//

#include "repertoire_viewer_controller.h"


namespace repertoire_viewer {
    Controller::Controller(RepertoireService &service, QObject *parent)
        : QObject(parent),
          m_rep_service(service),
          m_view(new View()) {
        initConnections();
    }

    void Controller::getUciMovesForFEN(const Models::FEN& fen) {
        emit requestMoveModels(m_rep_service.get_moves_from_fen(fen));
    }

    void Controller::showMoves(const QList<Models::Move> &moves) const {
        m_view->updateMovesWidget(moves);
    }

    void Controller::initConnections() {
        connect(m_view, &View::move_clicked,
                this, [this](const Models::Move &move) { emit moveClicked(move.uci); });
    }
}
