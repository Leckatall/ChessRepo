//
// Created by Lecka on 09/03/2025.
//

#ifndef LICHESSSERVICE_H
#define LICHESSSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QMap>
#include <QHash>
#include <QString>
#include <QJsonObject>
#include <utility>

#include "domain/types/fen.h"
#include "domain/types/stats.h"
#include "models/datatypes.h"

namespace Infrastructure::Explorer {
class LichessExplorerService : public QObject {
    Q_OBJECT

public:
    // Setting up configs
    enum class Config {
        Variant,
        Modes,
        Speeds,
        Ratings,
        Since,
        Until
    };

    Q_ENUM(Config)

    // Struct to hold request parameters
    struct Configs {
        QMap<QString, QString> params{
            {"variant", "standard"},
            {"modes", "rated"},
            {"speeds", "rapid,blitz"},
            {"ratings", ""},
            {"since", ""},
            {"until", ""}
        };
        const QHash<Config, QString> keys{
            {Config::Variant, "variant"},
            {Config::Modes, "modes"},
            {Config::Speeds, "speeds"},
            {Config::Ratings, "ratings"},
            {Config::Since, "since"},
            {Config::Until, "until"}
        };
        QString &operator[](Config opt) { return params[keys.value(opt)]; }
        QString operator[](Config opt) const { return params.value(keys.value(opt)); }

        [[nodiscard]] bool isSet(Config opt) const { return !params.value(keys.value(opt)).isEmpty(); }
    };

    Configs &config(); // get configuration
    [[nodiscard]] QString config(Config key) const; // get config of 1 setting
    LichessExplorerService &config(Config key, const QString &value); // set config of 1 setting
    // get config of multiple settings
    [[nodiscard]] QMap<Config, QString> config(std::initializer_list<Config> keys) const;

    // set config of multiple settings
    LichessExplorerService &config(std::initializer_list<std::pair<Config, QString> > configs);

    // Setting up service

    explicit LichessExplorerService(QObject *parent = nullptr);

    explicit LichessExplorerService(Configs config, QObject *parent = nullptr);

    void fetch_opening_data(const Domain::Types::FEN &fen, const QString &play = {});

signals:
    // LichessService:: isn't redundant in signals
    // ReSharper disable once CppRedundantQualifier
    void gotPositionData(Models::PositionData position);

    // ReSharper disable once CppRedundantQualifier
    void gotMovesData(QList<Models::MoveData> moves);

    void errorOccurred(QString errorMsg);

private slots:
    void handleOpeningReply(QNetworkReply *reply);

    void handleNetworkError(const QString &errorMessage);

private:
    void initConnections();

    [[nodiscard]] QUrl buildApiUrl(const Domain::Types::FEN &fen) const;

    [[nodiscard]] static Models::PositionData parsePositionJson(const QJsonObject &json);

    [[nodiscard]] static Models::MoveData parseMoveJson(const QJsonObject &json);

    QNetworkAccessManager m_net_client;
    Configs m_config;
    const QString LICHESS_URL = "https://explorer.lichess.ovh/lichess";
};
}



#endif //LICHESSSERVICE_H
