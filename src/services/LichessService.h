#ifndef _LICHESSSERVICE_H
#define _LICHESSSERVICE_H


namespace Models { class FEN; } 
namespace Models { struct MoveData; } 

typedef QObject typedef37;
class LichessService : public typedef37 {
  Q_OBJECT
  public:
    enum class Config {
      Variant,
      Modes,
      Speeds,
      Ratings,
      Since,
      Until
    };

    Configs & config();

    // get configuration
    QString config(Config key) const;

    // get config of 1 setting
    LichessService & config(Config key, const QString & value);

    // set config of 1 setting
    // get config of multiple settings
    QMap<Config, QString> config(std::initializer_list<Config> keys) const;

    // set config of multiple settings
    LichessService & config(std::initializer_list<std::pair<Config, QString> > configs);

    // Setting up service
    explicit LichessService(QObject * parent = nullptr);

    explicit LichessService(Configs config, QObject * parent = nullptr);

    void fetch_opening_data(const Models::FEN & fen, const QString & play = {});

  signals:    // LichessService:: isn't redundant in signals
    // ReSharper disable once CppRedundantQualifier
    void gotPositionData(Models::PositionData _t1);

    // ReSharper disable once CppRedundantQualifier
    void gotMovesData(QList<Models::MoveData> _t1);

    void errorOccurred(QString _t1);

  private slots:
  private:
    void handleOpeningReply(QNetworkReply * reply);

    void handleNetworkError(const QString & errorMessage);

    void initConnections();

    QUrl buildApiUrl(const Models::FEN & fen, const QString & play) const;

    static Models::PositionData parsePositionJson(const QJsonObject & json);

    static Models::MoveData parseMoveJson(const QJsonObject & json);

    QNetworkAccessManager m_net_client;

    Configs m_config;

    const QString LICHESS_URL=  "https://explorer.lichess.ovh/lichess";

};
#endif
