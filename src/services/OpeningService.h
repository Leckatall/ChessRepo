//
// Created by Lecka on 06/04/2025.
//

#ifndef OPENINGSERVICE_H
#define OPENINGSERVICE_H
#include <QObject>
#include <qtmetamacros.h>

#include "models/datatypes.h"


class OpeningService : public QObject {
    Q_OBJECT

public:
    explicit OpeningService(QObject *parent = nullptr) : QObject(parent) {
    }

    [[nodiscard]] static QStringList list_repertoires();

public slots:
    bool saveRepertoire(const Models::OpeningRepertoire &rep);

    Models::OpeningRepertoire getRepertoire(const QString &name);

signals:
    void repertoireChanged(const QString &name);

    void error(const QString &message);

private:
    static QString getRepoDir();

    static QString getRepertoireFilePath(const QString &name);

    Models::OpeningRepertoire load_repertoire(const QString &name);

    QHash<QString, Models::OpeningRepertoire> m_cached_repertoires;
};


#endif //OPENINGSERVICE_H
