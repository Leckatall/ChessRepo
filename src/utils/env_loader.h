//
// Created by Lecka on 08/03/2026.
//

#ifndef CHESSREPO_ENV_LOADER_H
#define CHESSREPO_ENV_LOADER_H
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QString>

inline QMap<QString, QString> loadEnv(const QString &filePath)
{
    QMap<QString, QString> vars;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return vars;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#')) continue;  // skip comments

        const int sep = line.indexOf('=');
        if (sep < 1) continue;

        const QString key   = line.left(sep).trimmed();
        QString       value = line.mid(sep + 1).trimmed();

        // Strip optional surrounding quotes  "value" or 'value'
        if (value.size() >= 2 &&
            ((value.startsWith('"')  && value.endsWith('"')) ||
             (value.startsWith('\'') && value.endsWith('\''))))
        {
            value = value.sliced(1, value.size() - 2);
        }

        vars.insert(key, value);
    }
    return vars;
}

#endif //CHESSREPO_ENV_LOADER_H