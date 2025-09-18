//
// Created by Lecka on 09/03/2025.
//

#include "explorer_controller.h"
#include "app/application.h"

#include <QGridLayout>
#include <QString>

namespace explorer {
    Controller::Controller(Infrastructure::Explorer::LichessExplorerService &service, QObject *parent)
        : QObject(parent),
          m_lichess_api(service),
          m_explorerTblModel(this),
          m_view(new View()) {
        m_view->setTblModel(&m_explorerTblModel);
        m_view->initTblUi();
        initConnections();
    }

    void Controller::initConnections() {
        // Updating the model
        // connect(&m_lichess_api, &Infrastructure::Explorer::LichessExplorerService::gotPositionData,
        //         this, &Controller::updatePositionData);
        // connect(&m_lichess_api, &Infrastructure::Explorer::LichessExplorerService::gotMovesData,
        //         this, &Controller::updateMoves);
        // Handling table clicks
        // View sends index to model to emit a signal of the data
        connect(m_view, &View::moveIndexClicked,
                &m_explorerTblModel, &TblModel::handleClick);
        connect(&m_explorerTblModel, &TblModel::moveClicked,
                this, [this](const Models::MoveData &move) { emit moveClicked(move.move.uci); });
    }

    void Controller::exploreFen(const QString &fen) const {
        // will emit signals to connected to: updatePositionData(pos) and updateMoves(moves)
        m_lichess_api.fetch_opening_data(Domain::Types::FEN(fen.toStdString()));
    }

    void Controller::updateMoves(const QList<Models::MoveData> &moves) {
        m_explorerTblModel.put_data(moves);
    }

    void Controller::updatePositionData(const Models::PositionData &position) {
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
}
