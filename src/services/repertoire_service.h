//
// Created by Lecka on 06/04/2025.
//

#ifndef OPENINGSERVICE_H
#define OPENINGSERVICE_H

#include <QObject>
#include <qtmetamacros.h>
#include <QtCore>

#include "models/datatypes.h"


class RepertoireService : public QObject {
    Q_OBJECT

public:
    explicit RepertoireService(QObject *parent = nullptr) : QObject(parent) {
        updateRepertoireList();

        // Monitors the repertoire directory for any changes
        m_watcher.addPath(getRepoDir());
        connect(&m_watcher, &QFileSystemWatcher::directoryChanged,
                this, &RepertoireService::onDirectoryChanged);
    }

    [[nodiscard]] QStringList get_repertoire_list();

    Models::Repertoire get_current_repertoire() { return m_current_repertoire; }

    void load_repertoire(const QString &name);

public slots:
    bool saveRepertoire(const Models::Repertoire &rep);

    Models::Repertoire getRepertoire(const QString &name);

signals:
    void repertoireListChanged();

    void repertoireChanged(const QString &name);

    void newRepertoireLoaded();

    void error(const QString &message);

private slots:
    void onDirectoryChanged();

private:
    static QString getRepoDir();

    static QString getRepertoireFilePath(const QString &name);

    void updateRepertoireList();

    Models::Repertoire read_repertoire_file(const QString &name);

    Models::Repertoire m_current_repertoire;

    QHash<QString, Models::Repertoire> m_cached_repertoires;
    QStringList m_repertoire_title_list;

    QFileSystemWatcher m_watcher;
};


#endif //OPENINGSERVICE_H
