//
// Created by Lecka on 18/09/2025.
//

#include "explorer_viewmodel.h"

using namespace Infrastructure::Features::Explorer;

namespace Presentation::Features::Explorer {
    ExplorerViewModel::ExplorerViewModel(LichessExplorerService &service,
                                         QObject *parent)
        : QObject(parent)
          , m_service(service)
          , m_tableModel(this) {
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
                this, [this](const Domain::Types::UCIMove &uci) { emit moveClicked(uci); });

        connect(this, &ExplorerViewModel::fenChanged,&m_service, &LichessExplorerService::fetch_opening_data);
        connect(&m_service, &LichessExplorerService::gotOpeningGraph,
                this, &ExplorerViewModel::onGotPositionData);
        connect(&m_service, &LichessExplorerService::errorOccurred,
                this, &ExplorerViewModel::onNetworkError);
    }

    void ExplorerViewModel::setFen(const QString &fen) {
        if (m_fen == fen)
            return;
        m_fen = fen;
        emit fenChanged(Domain::Types::FEN(m_fen.toStdString()));
    }

    void ExplorerViewModel::exploreCurrentFen() {
        if (m_fen.isEmpty()) {
            setErrorMessage(QStringLiteral("FEN is empty"));
            return;
        }
        setErrorMessage({});
        setLoading(true);

        m_service.fetch_opening_data(Domain::Types::FEN(m_fen.toStdString()));
    }

    void ExplorerViewModel::refresh() {
        exploreCurrentFen();
    }

    void ExplorerViewModel::onGotPositionData(const Domain::Types::PositionGraph &position) {
        m_tableModel.setGraph(position);
        updatePositionSummary(position.getNode(position.getRootKey())->stats);
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
