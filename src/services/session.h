#ifndef _SESSION_H
#define _SESSION_H


#include "LichessService.h"
#include "repertoire.h"

class Session : public typedef37 {
  Q_OBJECT
  public:
    static inline Session & instance() {
            static Session instance;
            return instance;
        };

    // Session data
    inline const QString & currentUser() const { return m_currentUser; };

    inline const Models::Repertoire & currentRepo() const { return m_currentRepo; };

    inline const QDateTime & sessionStart() const { return m_sessionStart; };

    // Session operations
    inline void startSession(const QString & username) {
            m_currentUser = username;
            m_sessionStart = QDateTime::currentDateTimeUtc();
            emit sessionStarted(username);
        };

    inline void setCurrentRepo(const Models::Repertoire & repo) {
            m_currentRepo = repo;
            emit repoChanged(repo);
        };

  signals:    void sessionStarted(const QString & _t1);

    void repoChanged(const Models::Repertoire & _t1);


  private:
    // From your code
    QString m_currentUser=  "Leckatall";

    Models::Repertoire m_currentRepo;

    QDateTime m_sessionStart;

    Session() = default;

};
#endif
