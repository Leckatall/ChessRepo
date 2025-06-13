//
// Created by Lecka on 06/04/2025.
//

#ifndef OPENINGSERVICE_H
#define OPENINGSERVICE_H

#include <QObject>
#include <qtmetamacros.h>
#include <QtCore>

#include "models/datatypes.h"


class OpeningService : public QObject {
    Q_OBJECT

public:
    explicit OpeningService(QObject *parent = nullptr) : QObject(parent) {
        updateRepertoireList();

        // Monitors the repertoire directory for any changes
        m_watcher.addPath(getRepoDir());
        connect(&m_watcher, &QFileSystemWatcher::directoryChanged,
                this, &OpeningService::onDirectoryChanged);
    }

    [[nodiscard]] QStringList get_repertoire_list();

public slots:
    bool saveRepertoire(const Models::OpeningRepertoire &rep);

    Models::OpeningRepertoire getRepertoire(const QString &name);

signals:
    void repertoireListChanged();

    void repertoireChanged(const QString &name);

    void error(const QString &message);

private slots:
    void onDirectoryChanged();

private:
    static QString getRepoDir();

    static QString getRepertoireFilePath(const QString &name);

    void updateRepertoireList();

    Models::OpeningRepertoire load_repertoire(const QString &name);

    QHash<QString, Models::OpeningRepertoire> m_cached_repertoires;
    QStringList m_repertoire_title_list;

    QFileSystemWatcher m_watcher;
};


#endif //OPENINGSERVICE_H
