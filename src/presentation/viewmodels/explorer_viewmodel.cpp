//
// Created by Lecka on 18/09/2025.
//

#include "explorer_viewmodel.h"

using namespace Infrastructure::Features::Explorer;

namespace Presentation::Features::Explorer {
    ExplorerViewModel::ExplorerViewModel(LichessExplorerService &service,
                                         Infrastructure::Features::Repertoire::RepertoirePersistence &persistence,
                                         QObject *parent)
        : QObject(parent),
          m_service(service),
          m_persistence(persistence),
          m_tableModel(this),
    m_fen(Domain::Types::FEN::startingPosition()) {
        initConnections();

        // Relay clicks from the table model upwards as UCIMove
        // connect(&m_tableModel, &TableModel::moveClicked, this, [this](const Domain::Types::UCIMove &uci) {
        //     emit moveClicked(uci);
        // });
    }

    void ExplorerViewModel::initConnections() {
        // Might cause an issue because of the using namespace if the signal don't put the redundant namespace before the class
        // Connect to service outputs

        connect(&m_tableModel, &TableModel::moveClicked,
                this, [this](const Domain::Types::UCIMove &uci) {
                    qDebug() << "emitting move clicked";
                    emit moveClicked(uci);
                });

        connect(this, &ExplorerViewModel::fenChanged, &m_service, &LichessExplorerService::fetch_opening_data);
        connect(&m_service, &LichessExplorerService::gotOpeningGraph,
                this, &ExplorerViewModel::onGotPositionData);
        connect(&m_service, &LichessExplorerService::errorOccurred,
                this, &ExplorerViewModel::onNetworkError);
    }

    void ExplorerViewModel::setFen(const Domain::Types::FEN &fen) {
        if (m_fen == fen) {
            qDebug() << "Cancelled emit bc fen unchanged";
            return;
        }
        m_fen = fen;
        emit fenChanged(m_fen);
    }

    void ExplorerViewModel::exploreCurrentFen() {
        if (!m_fen.data()) {
            setErrorMessage(QStringLiteral("FEN is empty"));
            return;
        }
        setErrorMessage({});
        setLoading(true);

        m_service.fetch_opening_data(m_fen);
    }

    void ExplorerViewModel::refresh() {
        exploreCurrentFen();
    }

    void ExplorerViewModel::indexClicked(const QModelIndex &index) {
        m_tableModel.handleClick(index);
    }

    void ExplorerViewModel::onGotPositionData(const Domain::Types::PositionGraph &position) {
        m_tableModel.setGraph(position);
    }

    void ExplorerViewModel::onNetworkError(const QString &message) {
        setLoading(false);
        setErrorMessage(message);
    }

    void ExplorerViewModel::setLoading(bool v) {
        if (m_loading == v) return;
        m_loading = v;
        emit loadingChanged();
    }

    void ExplorerViewModel::setErrorMessage(const QString &m) {
        if (m_errorMessage == m) return;
        m_errorMessage = m;
        emit errorMessageChanged();
    }

    void ExplorerViewModel::updatePositionSummary(const Domain::Types::PositionStats &position) {
        QString text = QString("Games: %1\nWhite Wins: %2\nDraws: %3\nBlack Wins: %4")
                .arg(position.games)
                .arg(position.white_wins)
                .arg(position.draws)
                .arg(position.black_wins);
        // if (position.opening) {
        //     text += QString("\nOpening(name: \"%1\" eco: \"%2\")")
        //             .arg(position.opening.name, position.opening.eco);
        // }
        if (m_positionSummary == text) return;
        m_positionSummary = text;
        emit positionSummaryChanged();
    }
}
