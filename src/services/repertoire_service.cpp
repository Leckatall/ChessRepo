
#include "repertoire_service.h"
#include "chess_primitives.h"

QStringList RepertoireService::get_repertoire_list() {

    return m_repertoire_title_list;
}

QList<Models::Move> RepertoireService::get_moves_from_fen() {

    const auto current_pos = m_current_repertoire.move_db.positions[fen];
    QList<Models::Move> moves;
    for (const auto& move : current_pos.moves) {
        moves.append(move.move);
    }
    return moves;
}

void RepertoireService::load_repertoire() {

    if (m_cache.contains(name)) {
        m_current_repertoire = m_cache[name];
    }else {
        m_current_repertoire = read_repertoire_file(name);
    }
    emit newRepertoireLoaded();
}

bool RepertoireService::saveRepertoire() {

    QFile file(getRepertoireFilePath(rep.header.name));
    if (!file.open(QIODevice::WriteOnly)) {
        emit error(QString("Could not open file for writing: %1").arg(file.errorString()));
        return false;
    }

    QJsonObject root;
    root["name"] = rep.header.name;
    root["forWhite"] = rep.header.forWhite;
    root["description"] = rep.header.description;
    root["author"] = rep.header.author;
    root["createdAt"] = rep.header.createdAt.toString(Qt::ISODate);

    QJsonArray positions;
    for (auto it = rep.move_db.positions.begin(); it != rep.move_db.positions.end(); ++it) {
        QJsonObject pos;
        pos["fen"] = it.key();
        pos["comment"] = it.value().info.comment;
        pos["lastPlayed"] = it.value().info.lastPlayed.toString(Qt::ISODate);
        pos["createdAt"] = it.value().info.createdAt.toString(Qt::ISODate);
        pos["openingEco"] = it.value().info.opening.eco;
        pos["openingName"] = it.value().info.opening.name;

        // Save user stats
        QJsonObject userStats;
        userStats["timesPlayed"] = it.value().info.user_stats.games;
        userStats["whiteWins"] = it.value().info.user_stats.white_wins;
        userStats["draws"] = it.value().info.user_stats.draws;
        userStats["blackWins"] = it.value().info.user_stats.black_wins;
        pos["userStats"] = userStats;

        // Save API stats
        QJsonObject apiStats;
        apiStats["timesPlayed"] = it.value().info.api_stats.games;
        apiStats["whiteWins"] = it.value().info.api_stats.white_wins;
        apiStats["draws"] = it.value().info.api_stats.draws;
        apiStats["blackWins"] = it.value().info.api_stats.black_wins;
        apiStats["openingEco"] = it.value().info.api_stats.opening.eco;
        apiStats["openingName"] = it.value().info.api_stats.opening.name;
        pos["apiStats"] = apiStats;

        // Save moves
        QJsonArray moves;
        for (const auto &move : it.value().moves) {
            QJsonObject moveObj;
            moveObj["uci"] = move.move.uci;
            moveObj["san"] = move.move.san;
            moveObj["comment"] = move.comment;
            moveObj["toPosition"] = move.targetPosition->fen;
            moves.append(moveObj);
        }
        pos["moves"] = moves;

        positions.append(pos);
    }
    root["positions"] = positions;

    if (const QJsonDocument doc(root); file.write(doc.toJson()) == -1) {
        emit error(QString("Failed to write data: %1").arg(file.errorString()));
        return false;
    }

    m_cache[rep.header.name] = rep;
    emit repertoireChanged(rep.header.name);
    return true;
}

Models::Repertoire RepertoireService::getRepertoire() {

    auto it = m_cache.find(name);
    if (it != m_cache.end()) {
        return it.value();
    }
    return read_repertoire_file(name);
}

// SIGNAL 0

void RepertoireService::repertoireListChanged() {

    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1

void RepertoireService::repertoireChanged(const QString & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2

void RepertoireService::newRepertoireLoaded() {

    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3

void RepertoireService::error(const QString & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

void RepertoireService::onDirectoryChanged() {

    updateRepertoireList();
    m_cache.clear();
    qDebug() << "Repertoire directory modified. repertoire cache cleared";
    emit repertoireListChanged();
}

QString RepertoireService::getRepoDir()
{

    // TODO: Consider moving to a config class
    return R"(C:\Users\Lecka\CLionProjects\ChessReop\RepoDir)";
}

QString RepertoireService::getRepertoireFilePath()
{

    return QDir(getRepoDir()).filePath(name + ".json");
}

void RepertoireService::updateRepertoireList() {

    m_repertoire_title_list = QDir(getRepoDir()).entryList({"*.json"}, QDir::Files)
        .replaceInStrings(".json", "");
}

Models::Repertoire RepertoireService::read_repertoire_file() {

    QFile file(getRepertoireFilePath(name));
    if (!file.open(QIODevice::ReadOnly)) {
        emit error(QString("Could not open file for reading: %1").arg(file.errorString()));
        return {};
    }

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    Models::Repertoire repertoire;
    repertoire.header = Models::RepertoireInfo(
        root["name"].toString(),
        root["forWhite"].toBool(),
        root["description"].toString(),
        root["author"].toString()
    );
    repertoire.header.createdAt = QDateTime::fromString(root["createdAt"].toString(), Qt::ISODate);

    QJsonArray positions = root["positions"].toArray();
    for (const auto &posRef : positions) {
        QJsonObject pos = posRef.toObject();
        Models::FEN fen(pos["fen"].toString());
        Models::Position position(fen);

        position.info.comment = pos["comment"].toString();
        position.info.lastPlayed = QDateTime::fromString(pos["lastPlayed"].toString(), Qt::ISODate);
        position.info.createdAt = QDateTime::fromString(pos["createdAt"].toString(), Qt::ISODate);
        position.info.opening.eco = pos["openingEco"].toString();
        position.info.opening.name = pos["openingName"].toString();

        // Load user stats
        auto userStatsObj = pos["userStats"].toObject();
        position.info.user_stats.games = userStatsObj["timesPlayed"].toInt();
        position.info.user_stats.white_wins = userStatsObj["whiteWins"].toInt();
        position.info.user_stats.draws = userStatsObj["draws"].toInt();
        position.info.user_stats.black_wins = userStatsObj["blackWins"].toInt();


        // Load API stats
        auto apiStatsObj = pos["apiStats"].toObject();
        position.info.api_stats.games = apiStatsObj["timesPlayed"].toInt();
        position.info.api_stats.white_wins = apiStatsObj["whiteWins"].toInt();
        position.info.api_stats.draws = apiStatsObj["draws"].toInt();
        position.info.api_stats.black_wins = apiStatsObj["blackWins"].toInt();
        position.info.api_stats.opening.eco = apiStatsObj["openingEco"].toString();
        position.info.api_stats.opening.name = apiStatsObj["openingName"].toString();

        // Load moves
        QJsonArray movesArray = pos["moves"].toArray();
        for (const auto &moveRef : movesArray) {
            QJsonObject moveObj = moveRef.toObject();
            Models::Move move(moveObj["uci"].toString(), moveObj["san"].toString());
            Models::FEN toPos(moveObj["toPosition"].toString());
            position.moves.append(Models::MoveEdge(move, nullptr, moveObj["comment"].toString()));
        }

        repertoire.move_db.positions[fen] = position;
    }

    m_cache[name] = repertoire;
    return repertoire;
}

