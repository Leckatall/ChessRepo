//
// Created by Lecka on 19/09/2025.
//

#include "repertoire_persistence.h"

#include <QDir>
#include <qfilesystemwatcher.h>
#include <QJsonDocument>
#include <QJsonObject>

namespace Infrastructure::Features::Repertoire {
    RepertoirePersistence::RepertoirePersistence(QObject* parent): QObject(parent) {
        updateRepertoireList();

        // Monitors the repertoire directory for any changes
        m_watcher.addPath(REPERTOIRE_DIR.data());
        connect(&m_watcher, &QFileSystemWatcher::directoryChanged,
                this, &RepertoirePersistence::onDirectoryChanged);
    }
    bool RepertoirePersistence::save_repertoire(const Domain::Types::Repertoire::RepertoireData &repertoire, const bool overwrite) {
        QFile file(REPERTOIRE_DIR.data() + QString::fromStdString(repertoire.header.name) + ".json");
        if (overwrite && file.exists()) {
            qDebug() << "Repertoire already exists";
            return false;
        }
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Could not open file for writing: " << file.errorString();
            //emit error(QString("Could not open file for writing: %1").arg(file.errorString()));
            return false;
        }

        if (const QJsonDocument doc(toJson(repertoire)); file.write(doc.toJson()) == -1) {
            qDebug() << "Failed to write data: " << file.errorString();
            //emit error(QString("Failed to write data: %1").arg(file.errorString()));
            return false;
        }

        m_cached_repertoires[repertoire.header.name] = repertoire;
        //emit repertoireChanged(repertoire.name);
        return true;

    }

    void RepertoirePersistence::updateRepertoireList() {
        m_repertoire_list.clear();
        QStringList repertoire_list = QDir(REPERTOIRE_DIR.data()).entryList({"*.json"}, QDir::Files)
            .replaceInStrings(".json", "");
        m_repertoire_list.reserve(repertoire_list.size());
        for (const auto repertoire : repertoire_list) {
            m_repertoire_list.push_back(repertoire.toStdString());
        }
    }
    void RepertoirePersistence::onDirectoryChanged() {
        updateRepertoireList();
        m_cached_repertoires.clear();
        qDebug() << "Repertoire directory modified. repertoire cache cleared";
        emit repertoireListChanged();
    }
    // QJsonObject RepertoirePersistence::toJson(const Domain::Types::Repertoire::Header &header) {
    //     QJsonObject root;
    //     root["name"] = QString::fromStdString(header.name);
    //     root["forWhite"] = header.forWhite;
    //     root["createdAt"] = QJsonValue(QDateTime::fromStdTimePoint({header.createdAt}));
    //     root["author"] = QString::fromStdString(header.author);
    //     return root;
    // }
    //
    // QJsonObject RepertoirePersistence::toJson(const Domain::Types::PositionGraph::PositionGraph &graph) {
    //
    // }

    QJsonDocument RepertoirePersistence::toJson(const Domain::Types::Repertoire::RepertoireData &repertoire) {
        const QJsonValue rep_json = QJsonValue::fromVariant(QVariant::fromValue(repertoire));
        qDebug() << "JSON of repertoire:\n" << rep_json;
        return QJsonDocument(rep_json.toObject());
    }
}

