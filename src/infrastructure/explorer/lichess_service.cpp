//
// Created by Lecka on 09/03/2025.
//

#include "lichess_service.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <utility>
#include <QDebug>

namespace Infrastructure::Explorer {
    LichessExplorerService::LichessExplorerService(QObject *parent)
        : QObject(parent),
          m_net_client(this) {
        initConnections();
    }

    LichessExplorerService::LichessExplorerService(Configs config, QObject *parent)
        : QObject(parent),
          m_net_client(this),
          m_config(std::move(config)) {
        initConnections();
    }

    LichessExplorerService::Configs &LichessExplorerService::config() { return m_config; }

    QString LichessExplorerService::config(const Config key) const { return m_config[key]; }

    LichessExplorerService &LichessExplorerService::config(Config key, const QString &value) {
        m_config[key] = value;
        return *this;
    }

    QMap<LichessExplorerService::Config, QString> LichessExplorerService::config(
        std::initializer_list<Config> keys) const {
        QMap<Config, QString> result;
        for (const auto &key: keys) {
            result[key] = m_config[key];
        }
        return result;
    }

    LichessExplorerService &LichessExplorerService::config(std::initializer_list<std::pair<Config, QString> > configs) {
        for (const auto &[key, value]: configs) {
            m_config[key] = value;
        }
        return *this;
    }

    void LichessExplorerService::fetch_opening_data(const Domain::Types::FEN &fen, const QString &play) {
        const QUrl url = buildApiUrl(fen);
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_net_client.get(request);

        connect(reply, &QNetworkReply::finished,
                [this, reply] {
                    handleOpeningReply(reply);
                    reply->deleteLater();
                });
    }

    /**
     * @brief Constructs a Lichess API URL using the provided FEN string and optional play parameter.
     *
     * This method assembles a URL for interacting with the Lichess API's Explorer service, allowing
     * the user to query chess data based on a specific FEN.
     * It also integrates any additional configuration parameters defined in the LichessExplorerService
     * instance.
     *
     * @param fen The FEN representation of a chess position. Can be empty if not required.
     * @return A QUrl object representing the fully constructed API URL, ready for use in network requests.
     */
    QUrl LichessExplorerService::buildApiUrl(const Domain::Types::FEN &fen) const {
        QUrl url(LICHESS_URL);
        QUrlQuery query;

        if (!fen.empty()) {
            query.addQueryItem("fen", QString::fromStdString(fen));
        }

        // Add configuration parameters
        for (auto [key, value]: m_config.params.asKeyValueRange()) {
            if (!value.isEmpty()) {
                query.addQueryItem(key, value);
            }
        }

        url.setQuery(query);
        return url;
    }

    Models::PositionData LichessExplorerService::parsePositionJson(const QJsonObject &json) {
        std::int64_t white_wins = json.value("white").toInt();
        std::int64_t draws = json.value("draws").toInt();
        std::int64_t black_wins = json.value("black").toInt();
        std::int64_t games = white_wins + draws + black_wins;
        Models::Opening opener;
        if (auto openingVal = json.value("opening"); !openingVal.isNull()) {
            auto opening = openingVal.toObject();
            opener.name = opening.value("name").toString();
            opener.eco = opening.value("eco").toString();
        }
        return {games, white_wins, draws, black_wins, opener};
    }


    Models::MoveData LichessExplorerService::parseMoveJson(const QJsonObject &json) {
        QString uci = json.value("uci").toString();
        QString san = json.value("san").toString();

        return {{uci, san}, parsePositionJson(json)};
    }


    void LichessExplorerService::handleOpeningReply(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const auto doc = QJsonDocument::fromJson(reply->readAll()).object();

            Models::PositionData current_position = parsePositionJson(doc);
            emit gotPositionData(current_position);
            auto jsonMoves = doc.value("moves").toArray();
            QList<Models::MoveData> moves;

            for (auto jsonMove: jsonMoves) {
                auto jsonObj = jsonMove.toObject();
                moves.append(parseMoveJson(jsonObj));
            }
            emit gotMovesData(moves);
        } else {
            emit errorOccurred(reply->errorString());
        }
    }

    void LichessExplorerService::handleNetworkError(const QString &errorMessage) {
        qDebug() << QString("Network error: %1").arg(errorMessage);
    }

    void LichessExplorerService::initConnections() {
        connect(this, &LichessExplorerService::errorOccurred, this, &LichessExplorerService::handleNetworkError);
    }
}
