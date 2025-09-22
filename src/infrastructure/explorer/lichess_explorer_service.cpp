//
// Created by Lecka on 09/03/2025.
//

#include "lichess_explorer_service.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <utility>

#include "domain/types/position/position_graph.h"

namespace Infrastructure::Features::Explorer {
    LichessExplorerService::LichessExplorerService(QObject *parent)
        : QObject(parent),
          m_net_client(this) {
        initConnections();
    }

    LichessExplorerService::LichessExplorerService(const LichessRequestBuilder::Configs &config, QObject *parent)
        : QObject(parent),
          m_net_client(this),
          m_request_builer(config) {
        initConnections();
    }

    void LichessExplorerService::fetch_opening_data(const Domain::Types::FEN &fen) {
        if (m_cache.hasNode(fen)) {
            emit gotOpeningGraph(m_cache.getSubGraph(fen));
            return;
        }
        QNetworkRequest request(m_request_builer.buildApiUrl(fen));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_net_client.get(request);

        connect(reply, &QNetworkReply::finished,
                [this, reply, fen] {
                    handleOpeningReply(fen, reply);
                    reply->deleteLater();
                });
    }

    void LichessExplorerService::handleOpeningReply(const Domain::Types::FEN &fen, QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const auto opening_graph = LichessExplorerParser::handle_reponse(fen, reply->readAll());
            m_cache << opening_graph;
            emit gotOpeningGraph(opening_graph);
        } else {
            qDebug() << "error!!";
            emit errorOccurred(reply->errorString());
        }
    }

    void LichessExplorerService::handleNetworkError(const QString &errorMessage) {
        qDebug() << QString("Network error: %1").arg(errorMessage);
    }

    void LichessExplorerService::initConnections() const {
        connect(this, &LichessExplorerService::errorOccurred, this, &LichessExplorerService::handleNetworkError);
    }
}
