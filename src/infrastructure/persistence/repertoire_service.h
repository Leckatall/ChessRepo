//
// Created by Lecka on 06/04/2025.
//

#ifndef OPENINGSERVICE_H
#define OPENINGSERVICE_H

#include <QObject>
#include <qtmetamacros.h>
#include <QtCore>

#include "repertoire_persistence.h"

namespace Infrastructure::Features::Repertoire {
    class RepertoireService : public QObject {
        Q_OBJECT

    public:
        explicit RepertoireService(RepertoirePersistence &persistence, QObject *parent = nullptr)
            : QObject(parent),
              m_persistence(persistence) {
            initConnections();
        }

        [[nodiscard]] QStringList getRepertoireList() { return m_repertoire_title_list; }

        Domain::Types::Repertoire::RepertoireData *getRepertoire() { return &m_current_repertoire; }

    public slots:
        void saveLoadedRepertoire() const;

        void loadRepertoire(const QString &name);

        void onRepertoireListChanged();

    signals:
        void repertoireListChanged();

        void repertoireLoaded();

    private:
        void initConnections();

        RepertoirePersistence &m_persistence;
        Domain::Types::Repertoire::RepertoireData m_current_repertoire;

        QStringList m_repertoire_title_list;
    };
}


#endif //OPENINGSERVICE_H
