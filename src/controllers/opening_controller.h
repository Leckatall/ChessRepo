//
// Created by Lecka on 05/03/2025.
//

#ifndef OPENING_CONTROLLER_H
#define OPENING_CONTROLLER_H
#include <QObject>


class OpeningController : public QObject {
    Q_OBJECT

public:
    explicit OpeningController(QObject* parent = nullptr);

    // Opening management methods
    Q_INVOKABLE Opening* createOpening(const QString& name, const QString& moves);
    Q_INVOKABLE void saveOpening(Opening* opening);
    Q_INVOKABLE void deleteOpening(Opening* opening);
    Q_INVOKABLE QList<Opening*> loadOpenings();

    // Chess move-related methods
    Q_INVOKABLE void validateMove(const QString& move);
    Q_INVOKABLE void fetchOpeningExplorerData(const QString& moves);

    signals:
        void openingCreated(Opening* opening);
    void openingDeleted(Opening* opening);
    void openingExplorerDataReceived(const QJsonObject& explorerData);

private:
    QList<Opening*> m_openings;
    ApiService* m_apiService;
};



#endif //OPENING_CONTROLLER_H
