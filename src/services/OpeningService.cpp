//
// Created by Lecka on 06/04/2025.
//

#include "OpeningService.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QDir"


Models::OpeningRepertoire OpeningService::getRepertoire(const QString &name) {
    auto it = m_cached_repertoires.find(name);
    if (it != m_cached_repertoires.end()) {
        return it.value();
    }
    return load_repertoire(name);
}

void OpeningService::onDirectoryChanged() {
    updateRepertoireList();
    m_cached_repertoires.clear();
    qDebug() << "Repertoire directory modified. repertoire cache cleared";
    emit repertoireListChanged();
}

QString OpeningService::getRepoDir() {
    // TODO: Consider moving to a config class
    return R"(C:\Users\Lecka\CLionProjects\ChessReop\RepoDir)";
}

QString OpeningService::getRepertoireFilePath(const QString& name) {
    return QDir(getRepoDir()).filePath(name + ".json");
}

void OpeningService::updateRepertoireList() {
    m_repertoire_title_list = QDir(getRepoDir()).entryList({"*.json"}, QDir::Files)
        .replaceInStrings(".json", "");
}

QStringList OpeningService::get_repertoire_list() {
    return m_repertoire_title_list;
}

bool OpeningService::saveRepertoire(const Models::OpeningRepertoire &rep) {
    QFile file(getRepertoireFilePath(rep.name));
    if (!file.open(QIODevice::WriteOnly)) {
        emit error(QString("Could not open file for writing: %1").arg(file.errorString()));
        return false;
    }

    QJsonObject root;
    root["name"] = rep.name;
    root["forWhite"] = rep.forWhite;
    root["createdAt"] = rep.createdAt.toString(Qt::ISODate);
    root["Author"] = rep.author;

    QJsonArray positions;
    for (auto it = rep.positions.begin(); it != rep.positions.end(); ++it) {
        QJsonObject pos;
        pos["fen"] = it.key();
        pos["recommendedMove"] = it.value().recommendedMove;
        pos["wins"] = it.value().wins;
        pos["draws"] = it.value().draws;
        pos["losses"] = it.value().losses;
        pos["timesPlayed"] = it.value().timesPlayed;
        pos["comment"] = it.value().comment;
        pos["lastPlayed"] = it.value().lastPlayed.toString(Qt::ISODate);

        QJsonObject responses;
        for (auto respIt = it.value().responses.begin(); respIt != it.value().responses.end(); ++respIt) {
            responses[respIt.key()] = respIt.value();
        }
        pos["responses"] = responses;

        positions.append(pos);
    }
    root["positions"] = positions;

    if (const QJsonDocument doc(root); file.write(doc.toJson()) == -1) {
        emit error(QString("Failed to write data: %1").arg(file.errorString()));
        return false;
    }

    m_cached_repertoires[rep.name] = rep;
    emit repertoireChanged(rep.name);
    return true;
}
Models::OpeningRepertoire OpeningService::load_repertoire(const QString &name) {
    QFile file(getRepertoireFilePath(name));
    if (!file.open(QIODevice::ReadOnly)) {
        emit error(QString("Could not open file for reading: %1").arg(file.errorString()));
        return {}; // Return empty repertoire for white - should discard if this is returned
    }

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    Models::OpeningRepertoire rep(
        root["name"].toString(),
        root["forWhite"].toBool()
    );
    rep.createdAt = QDateTime::fromString(root["createdAt"].toString(), Qt::ISODate);
    rep.author = root["author"].toString();

    QJsonArray positions = root["positions"].toArray();
    for (const auto& posRef : positions) {
        QJsonObject pos = posRef.toObject();
        Models::OpeningPosition position(Models::FEN(pos["fen"].toString()));
        position.recommendedMove = Models::UCIMove(pos["recommendedMove"].toString());
        position.wins = pos["wins"].toInt();
        position.draws = pos["draws"].toInt();
        position.losses = pos["losses"].toInt();
        position.timesPlayed = pos["timesPlayed"].toInt();
        position.comment = pos["comment"].toString();
        position.lastPlayed = QDateTime::fromString(pos["lastPlayed"].toString(), Qt::ISODate);

        QJsonObject responses = pos["responses"].toObject();
        for (auto it = responses.begin(); it != responses.end(); ++it) {
            position.responses[Models::UCIMove(it.key())] = Models::FEN(it.value().toString());
        }

        rep.positions[position.position] = position;
    }

    m_cached_repertoires[name] = rep;
    return rep;
}