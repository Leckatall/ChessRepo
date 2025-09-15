
#include "repertoire_viewer_controller.h"
#include "repertoire_service.h"
#include "repertoire_view.h"
#include "chess_primitives.h"

namespace repertoire_viewer {

Controller::Controller(::RepertoireService & service, QObject * parent)
        : QObject(parent),
          m_rep_service(service),
          m_view(new View()) {

        initConnections();
}

void Controller::getUciMovesForFEN() {

        emit requestMoveModels(m_rep_service.get_moves_from_fen(fen));
}

void Controller::showMoves() const {

        m_view->updateMovesWidget(moves);
}

// SIGNAL 0

void Controller::moveClicked(Models::UCIMove _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void Controller::requestMoveModels(QList<Models::UCIMove> _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

void Controller::initConnections() {

        connect(m_view, &View::move_clicked,
                this, [this](const Models::Move &move) { emit moveClicked(move.uci); });
}


} // namespace repertoire_viewer
