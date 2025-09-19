//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_PERSISTENCE_H
#define CHESSREPO_REPERTOIRE_PERSISTENCE_H
#include <qfilesystemwatcher.h>
#include <QObject>

#include "domain/repertoire/repertoire.h"
#include "domain/types/position/position_graph.h"

namespace Infrastructure::Features::Repertoire {
    class RepertoirePersistence : public QObject {
        Q_OBJECT

    public:
        RepertoirePersistence(QObject *parent = nullptr);

        void updateRepertoireList();

        [[nodiscard]] std::vector<std::string> get_repertoire_list() const { return m_repertoire_list; }

        bool save_repertoire(const Domain::Types::Repertoire::RepertoireData &repertoire, bool overwrite = false);

        Domain::Types::Repertoire::RepertoireData get_repertoire(const QString &name);

    public slots:
        void onDirectoryChanged();


    signals:
        void repertoireListChanged();

    private:
        constexpr static std::string_view REPERTOIRE_DIR = "../../../persistence/";

        QJsonDocument toJson(const Domain::Types::Repertoire::RepertoireData &repertoire);

        // QJsonObject toJson(const Domain::Types::Repertoire::Header &header);
        // QJsonObject toJson(const Domain::Types::PositionGraph &graph);

        QFileSystemWatcher m_watcher;

        std::unordered_map<std::string, Domain::Types::Repertoire::RepertoireData> m_cached_repertoires;
        std::vector<std::string> m_repertoire_list;
    };
}


#endif //CHESSREPO_REPERTOIRE_PERSISTENCE_H
