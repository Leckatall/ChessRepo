
#include "explorer_controller.h"
#include "LichessService.h"
#include "explorer_view.h"
#include "chess_primitives.h"

namespace explorer {

// TODO: Add engine support
// TODO: Add integration with openerController and highlight prepped moves
Controller::Controller(::LichessService & service, QObject * parent)
        : QObject(parent),
          m_lichess_api(service),
          m_explorerTblModel(this),
          m_view(new View()) {

        m_view->setTblModel(&m_explorerTblModel);
        m_view->initTblUi();
        initConnections();
}

void Controller::exploreFen() const {

        // will emit signals to connected to: updatePositionData(pos) and updateMoves(moves)
        m_lichess_api.fetch_opening_data(fen);
}

void Controller::updateMoves() {

        m_explorerTblModel.put_data(moves);
}

void Controller::updatePositionData() {

        m_current_position = position;
        QString new_text = "Games: " + QString::number(position.games) +
                           "\nWhite Wins: " + QString::number(position.white_wins) +
                           "\nDraws: " + QString::number(position.draws) +
                           "\nBlack Wins: " + QString::number(position.black_wins);
        if (position.opening) {
            new_text += QString("\nOpening(name: \"%1\" eco: \"%2\")").arg(position.opening.name, position.opening.eco);
        }
        m_view->updatePositionLabel(new_text);
        m_explorerTblModel.set_root_position(position);
}

// SIGNAL 0

void Controller::moveClicked(Models::UCIMove _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

void Controller::initConnections() {

        // Updating the model
        connect(&m_lichess_api, &LichessService::gotPositionData,
                this, &Controller::updatePositionData);
        connect(&m_lichess_api, &LichessService::gotMovesData,
                this, &Controller::updateMoves);
        // Handling table clicks
        // View sends index to model to emit a signal of the data
        connect(m_view, &View::moveIndexClicked,
                &m_explorerTblModel, &TblModel::handleClick);
        connect(&m_explorerTblModel, &TblModel::moveClicked,
                this, [this](const Models::MoveData &move) { emit moveClicked(move.move.uci); });
}


} // namespace explorer
