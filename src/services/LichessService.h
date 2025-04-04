//
// Created by Lecka on 09/03/2025.
//

#ifndef LICHESSSERVICE_H
#define LICHESSSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <utility>

#include "models/datatypes.h"


class LichessService : public QObject {
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
        const QMap<Config, QString> keys{
            {Config::Variant, "variant"},
            {Config::Modes, "modes"},
            {Config::Speeds, "speeds"},
            {Config::Ratings, "ratings"},
            {Config::Since, "since"},
            {Config::Until, "until"}
        };
        QString &operator[](const Config opt) { return params[keys[opt]]; }
        const QString &operator[](const Config opt) const { return std::move(params[keys[opt]]); }

        [[nodiscard]] bool isSet(const Config opt) const { return !params[keys[opt]].isEmpty(); }
    };

    Configs &config(); // get configuration
    [[nodiscard]] QString config(Config key) const; // get config of 1 setting
    LichessService &config(Config key, const QString &value); // set config of 1 setting
    // get config of multiple settings
    [[nodiscard]] QMap<Config, QString> config(std::initializer_list<Config> keys) const;

    // set config of multiple settings
    LichessService &config(std::initializer_list<std::pair<Config, QString> > configs);

    // Setting up service

    explicit LichessService(QObject *parent = nullptr);

    explicit LichessService(Configs config, QObject *parent = nullptr);

    void fetch_opening_data(QString fen, const QString &play = {});

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

    [[nodiscard]] QUrl buildApiUrl(QString fen, const QString &play) const;

    [[nodiscard]] static Models::PositionData parsePositionJson(const QJsonObject &json);

    [[nodiscard]] static Models::MoveData parseMoveJson(const QJsonObject &json);

    QNetworkAccessManager m_net_client;
    Configs m_config;
    const QString LICHESS_URL = "https://explorer.lichess.ovh/lichess";
};


#endif //LICHESSSERVICE_H
