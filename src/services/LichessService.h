//
// Created by Lecka on 09/03/2025.
//

#ifndef LICHESSSERVICE_H
#define LICHESSSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>

struct MoveData {
    QString uci;
    QString san;
    int games;
    int white_wins;
    int black_wins;
    int draws;
    QString opening_name;
    QString opening_eco;
};

class LichessService: public QObject {
public:
    explicit LichessService(QObject *parent = nullptr);

    void fetchPossibleMovesData(const QString &fen);


signals:
    void movesDataReceived(MoveData current_move, QList<MoveData> moves);

    void errorOccurred(QString errorMsg);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    [[nodiscard]] static MoveData getMoveInfo(const QJsonObject& move_json);
    QNetworkAccessManager* m_net_client;
    QString LICHESS_URL = "https://explorer.lichess.ovh/lichess?";
};


#endif //LICHESSSERVICE_H
