//
// Created by Lecka on 09/03/2025.
//

#include "LichessService.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

LichessService::LichessService(QObject *parent): m_net_client(new QNetworkAccessManager(this)) {

}

void LichessService::fetchPossibleMovesData(const QString &fen) {
    const auto req = QNetworkRequest(QUrl(LICHESS_URL + "fen=" + fen));
    const auto *reply = m_net_client->get(req);

    connect(reply, &QNetworkReply::finished,
        this, &LichessService::onReplyFinished);
}

MoveData LichessService::getMoveInfo(const QJsonObject& move_json) {
    MoveData move;
    move.uci = move_json.value("uci").toString();
    move.san = move_json.value("san").toString();
    // moveData.games = jsonObj.value("games").toInt();

    // win counts
    move.white_wins = move_json.value("white").toInt();
    move.black_wins = move_json.value("black").toInt();
    move.draws = move_json.value("draws").toInt();

    move.games = move.white_wins + move.draws + move.black_wins;

    if(auto opening = move_json.value("opening").toObject(); !opening.isEmpty()) {
        move.opening_name = opening.value("opening_name").toString();
        move.opening_eco = opening.value("opening_eco").toString();
    }
    return move;
}

void LichessService::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        auto doc = QJsonDocument::fromJson(reply->readAll()).object();


        MoveData current_move = getMoveInfo(doc);

        auto jsonMoves = doc.value("moves").toArray();
        QList<MoveData> moves;

        for (auto jsonMove : jsonMoves) {
            auto jsonObj = jsonMove.toObject();
            moves.append(getMoveInfo(jsonObj));
        }
        emit movesDataReceived(current_move, moves);
    } else {
        emit errorOccurred(reply->errorString());
    }

    reply->deleteLater();
}


