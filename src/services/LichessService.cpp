//
// Created by Lecka on 09/03/2025.
//

#include "LichessService.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <utility>

LichessService::LichessService(QObject *parent)
    : QObject(parent),
      m_net_client(this) {
    initConnections();
}

LichessService::LichessService(Configs config, QObject *parent): QObject(parent),
                                                                 m_net_client(this),
                                                                 m_config(std::move(config)) {
    initConnections();
}

LichessService::Configs &LichessService::config() { return m_config; }

QString LichessService::config(const Config key) const { return m_config[key]; }

LichessService &LichessService::config(Config key, const QString &value) {
    m_config[key] = value;
    return *this;
}

QMap<LichessService::Config, QString> LichessService::config(std::initializer_list<Config> keys) const {
    QMap<Config, QString> result;
    for (const auto &key: keys) {
        result[key] = m_config[key];
    }
    return result;
}

LichessService &LichessService::config(std::initializer_list<std::pair<Config, QString> > configs) {
    for (const auto &[key, value]: configs) {
        m_config[key] = value;
    }
    return *this;
}

void LichessService::fetch_opening_data(QString fen, const QString &play) {
    const QUrl url = buildApiUrl(fen, play);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_net_client.get(request);

    connect(reply, &QNetworkReply::finished,
            [this, reply] {
                handleOpeningReply(reply);
                reply->deleteLater();
            });
}

QUrl LichessService::buildApiUrl(QString fen, const QString &play) const {
    QUrl url(LICHESS_URL);
    QUrlQuery query;

    // Add dynamic parameters
    if (!play.isEmpty()) {
        query.addQueryItem("play", play);
    }

    if (!fen.isEmpty()) {
        query.addQueryItem("fen", fen);
    }

    // Add configuration parameters
    for (auto [key, value]: m_config.params.asKeyValueRange()) {
        if(!value.isEmpty()) {
            query.addQueryItem(key, value);
        }
    }

    url.setQuery(query);
    return url;
}

LichessService::PositionData LichessService::parsePositionJson(const QJsonObject &json) {
    std::int64_t white_wins = json.value("white").toInt();
    std::int64_t draws = json.value("draws").toInt();
    std::int64_t black_wins = json.value("black").toInt();
    std::int64_t games = white_wins + draws + black_wins;
    Opening opener;
    if (auto openingVal = json.value("opening"); !openingVal.isNull()) {
        auto opening = openingVal.toObject();
        opener.name = opening.value("name").toString();
        opener.eco = opening.value("eco").toString();

    }
    return {games, white_wins, draws, black_wins, opener};
}


LichessService::MoveData LichessService::parseMoveJson(const QJsonObject &json) {
    QString uci = json.value("uci").toString();
    QString san = json.value("san").toString();

    return {uci, san, parsePositionJson(json)};
}


void LichessService::handleOpeningReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        const auto doc = QJsonDocument::fromJson(reply->readAll()).object();

        PositionData current_position = parsePositionJson(doc);
        emit gotPositionData(current_position);
        auto jsonMoves = doc.value("moves").toArray();
        QList<MoveData> moves;

        for (auto jsonMove: jsonMoves) {
            auto jsonObj = jsonMove.toObject();
            moves.append(parseMoveJson(jsonObj));
        }
        emit gotMovesData(moves);
    } else {
        emit errorOccurred(reply->errorString());
    }
}

void LichessService::handleNetworkError(const QString& errorMessage) {
    qDebug() << QString("Network error: %1").arg(errorMessage);
}

void LichessService::initConnections() {
    connect(this, errorOccurred, this, handleNetworkError);
}
