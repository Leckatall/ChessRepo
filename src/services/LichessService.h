//
// Created by Lecka on 09/03/2025.
//

#ifndef LICHESSSERVICE_H
#define LICHESSSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <utility>


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
#
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
    struct Opening {
        QString eco;
        QString name;

        Opening(QString eco_str, QString name_str): eco(std::move(eco_str)), name(std::move(name_str)) {
        }

        Opening() = default;
        explicit operator bool() const {return eco.isEmpty() and name.isEmpty();}
    };

    struct PositionData {
        std::int64_t games;
        std::int64_t white_wins;
        std::int64_t draws;
        std::int64_t black_wins;
        Opening opening;

        PositionData(const std::int64_t g, const std::int64_t w, const std::int64_t d, const std::int64_t b, Opening o = {})
            : games(g),
              white_wins(w),
              draws(d),
              black_wins(b),
              opening(std::move(o)) {
        }

    };

    struct MoveData {
        QString uci;
        QString san;
        PositionData position_data;

        MoveData(QString uci_str, QString san_str, PositionData position)
            : uci(std::move(uci_str)),
              san(std::move(san_str)),
              position_data(std::move(position)) {
        }
    };

    explicit LichessService(QObject *parent = nullptr);

    explicit LichessService(Configs config, QObject *parent = nullptr);

    void fetch_opening_data(QString fen, const QString &play = {});

signals:
    // LichessService:: isn't redundant in signals
    // ReSharper disable once CppRedundantQualifier
    void gotPositionData(LichessService::PositionData position);

    // ReSharper disable once CppRedundantQualifier
    void gotMovesData(QList<LichessService::MoveData> moves);

    void errorOccurred(QString errorMsg);

private slots:
    void handleOpeningReply(QNetworkReply *reply);

    void handleNetworkError(const QString& errorMessage);

private:
    void initConnections();
    [[nodiscard]] QUrl buildApiUrl(QString fen, const QString &play) const;

    [[nodiscard]] static PositionData parsePositionJson(const QJsonObject &json);

    [[nodiscard]] static MoveData parseMoveJson(const QJsonObject &json);

    QNetworkAccessManager m_net_client;
    Configs m_config;
    const QString LICHESS_URL = "https://explorer.lichess.ovh/lichess";
};


#endif //LICHESSSERVICE_H
