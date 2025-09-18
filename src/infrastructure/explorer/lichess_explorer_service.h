//
// Created by Lecka on 09/03/2025.
//

#ifndef LICHESSSERVICE_H
#define LICHESSSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <utility>

#include "lichess_explorer_parser.h"
#include "lichess_request_builder.h"
#include "domain/types/fen.h"
#include "models/datatypes.h"

namespace Infrastructure::Features::Explorer {
class LichessExplorerService : public QObject {
    Q_OBJECT

public:
    // Setting up service
    explicit LichessExplorerService(QObject *parent = nullptr);

    explicit LichessExplorerService(const LichessRequestBuilder::Configs &config, QObject *parent = nullptr);

    void fetch_opening_data(const Domain::Types::FEN &fen);

signals:
    void gotOpeningGraph(const Domain::Types::PositionGraph &position_graph);

    void errorOccurred(QString errorMsg);

private slots:
    void handleOpeningReply(const Domain::Types::FEN &fen, QNetworkReply *reply);

    static void handleNetworkError(const QString &errorMessage);

private:
    void initConnections() const;

    QNetworkAccessManager m_net_client;
    LichessRequestBuilder m_request_builer;
    LichessExplorerParser m_parser;

};
}



#endif //LICHESSSERVICE_H
