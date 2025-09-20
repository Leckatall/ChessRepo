//
// Created by Lecka on 19/09/2025.
//

#include "repertoire_persistence.h"

#include <QDir>
#include <qfilesystemwatcher.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QJson_parser.h"

namespace Infrastructure::Features::Repertoire {
    RepertoirePersistence::RepertoirePersistence(const std::string &repo_dir, QObject* parent): QObject(parent), m_directory(repo_dir) {
        updateRepertoireList();

        // Monitors the repertoire directory for any changes
        m_watcher.addPath(m_directory.data());
        connect(&m_watcher, &QFileSystemWatcher::directoryChanged,
                this, &RepertoirePersistence::onDirectoryChanged);
    }

    bool RepertoirePersistence::save_repertoire(const Domain::Types::Repertoire::RepertoireData &repertoire, const bool overwrite) {
        QFile file(m_directory.data() + QString::fromStdString(repertoire.header.name) + ".rep");
        if (overwrite && file.exists()) {
            qDebug() << "Repertoire already exists";
            return false;
        }
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Could not open file for writing: " << file.errorString();
            //emit error(QString("Could not open file for writing: %1").arg(file.errorString()));
            return false;
        }
        QDataStream stream(&file);
        stream << repertoire;
        // if ( file.write(doc.toJson()) == -1) {
        //     qDebug() << "Failed to write data: " << file.errorString();
        //     //emit error(QString("Failed to write data: %1").arg(file.errorString()));
        //     return false;
        // }

        m_cached_repertoires[repertoire.header.name] = repertoire;
        //emit repertoireChanged(repertoire.name);
        return true;

    }

    Domain::Types::Repertoire::RepertoireData RepertoirePersistence::get_repertoire(const std::string &name) {
        QFile file(m_directory.data() + QString::fromStdString(name) + REPERTOIRE_FILE_EXTENSION.data());
        if (m_cached_repertoires.contains(name)) {
            return m_cached_repertoires[name];
        }
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open file for writing: " << file.errorString();
            //emit error(QString("Could not open file for writing: %1").arg(file.errorString()));
            return {};
        }
        QDataStream stream(&file);
        Domain::Types::Repertoire::RepertoireData repertoire;
        stream >> repertoire;
        return repertoire;

    }

    void RepertoirePersistence::updateRepertoireList() {
        m_repertoire_list.clear();
        QStringList repertoire_list = QDir(m_directory.data()).entryList({"*" + REPERTOIRE_FILE_EXTENSION}, QDir::Files)
            .replaceInStrings(REPERTOIRE_FILE_EXTENSION.data(), "");
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

}

