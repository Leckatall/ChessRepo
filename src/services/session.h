//
// Created by Lecka on 12/06/2025.
//

#ifndef SESSION_H
#define SESSION_H
#include <QObject>

#include "models/datatypes.h"


class Session : public QObject {
    Q_OBJECT

public:
    static Session &instance() {
        static Session instance;
        return instance;
    }

    // Session data
    [[nodiscard]] const QString &currentUser() const { return m_currentUser; }
    [[nodiscard]] const Models::OpeningRepertoire &currentRepo() const { return m_currentRepo; }
    [[nodiscard]] const QDateTime &sessionStart() const { return m_sessionStart; }

    // Session operations
    void startSession(const QString &username) {
        m_currentUser = username;
        m_sessionStart = QDateTime::currentDateTimeUtc();
        emit sessionStarted(username);
    }

    void setCurrentRepo(const Models::OpeningRepertoire &repo) {
        m_currentRepo = repo;
        emit repoChanged(repo);
    }

signals:
    void sessionStarted(const QString &username);

    void repoChanged(const Models::OpeningRepertoire &repo);

private:
    QString m_currentUser = "Leckatall"; // From your code
    Models::OpeningRepertoire m_currentRepo;
    QDateTime m_sessionStart;

    Session() = default;
};

#endif //SESSION_H
