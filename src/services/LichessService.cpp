
#include "LichessService.h"
#include "chess_primitives.h"
#include "move.h"

Configs LichessService::config() {
 return m_config;
}

// get config of 1 setting
LichessService LichessService::config() {

    m_config[key] = value;
    return *this;
}

// set config of 1 setting
// get config of multiple settings
QMap<Config, QString> LichessService::config() const {

    QMap<Config, QString> result;
    for (const auto &key: keys) {
        result[key] = m_config[key];
    }
    return result;
}

// set config of multiple settings
LichessService LichessService::config() {

    for (const auto &[key, value]: configs) {
        m_config[key] = value;
    }
    return *this;
}

// Setting up service
LichessService::LichessService(QObject * parent)
    : QObject(parent),
      m_net_client(this) {

    initConnections();
}

LichessService::LichessService(Configs config, QObject * parent): QObject(parent),
                                                                 m_net_client(this),
                                                                 m_config(std::move(config)) {

    initConnections();
}

void LichessService::fetch_opening_data() {

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

// SIGNAL 0

void LichessService::gotPositionData(Models::PositionData _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void LichessService::gotMovesData(QList<Models::MoveData> _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2

void LichessService::errorOccurred(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

void LichessService::handleOpeningReply() {

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

void LichessService::handleNetworkError() {

    qDebug() << QString("Network error: %1").arg(errorMessage);
}

void LichessService::initConnections() {

    connect(this, errorOccurred, this, handleNetworkError);
}

QUrl LichessService::buildApiUrl() const {

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

Models::PositionData LichessService::parsePositionJson()
{

    std::int64_t white_wins = json.value("white").toInt();
    std::int64_t draws = json.value("draws").toInt();
    std::int64_t black_wins = json.value("black").toInt();
    std::int64_t games = white_wins + draws + black_wins;
    Models::OpeningTitle opener;
    if (auto openingVal = json.value("opening"); !openingVal.isNull()) {
        auto opening = openingVal.toObject();
        opener.name = opening.value("name").toString();
        opener.eco = opening.value("eco").toString();

    }
    return {games, white_wins, draws, black_wins, opener};
}

Models::MoveData LichessService::parseMoveJson()
{

    QString uci = json.value("uci").toString();
    QString san = json.value("san").toString();

    return {{uci, san}, parsePositionJson(json)};
}

