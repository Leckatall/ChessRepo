//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_PERSISTENCE_H
#define CHESSREPO_REPERTOIRE_PERSISTENCE_H
#include <qfilesystemwatcher.h>
#include <QIODevice>
#include <QObject>

#include "qt_serialization.h"
#include "domain/repertoire/repertoire.h"
#include "domain/types/position/position_graph.h"

class QFile;

using namespace Infrastructure::Features::Persistence;
namespace Infrastructure::Features::Repertoire {
    class RepertoirePersistence : public QObject {
        Q_OBJECT

    public:
        RepertoirePersistence(const std::string &repo_dir = "../../../persistence/", QObject *parent = nullptr);

        void updateRepertoireList();

        [[nodiscard]] std::vector<std::string> get_repertoire_list() const { return m_repertoire_list; }

        bool save_repertoire(const Domain::Types::Repertoire::RepertoireData &repertoire, bool overwrite = false);

        Domain::Types::Repertoire::RepertoireData get_repertoire(const std::string &name);

        void setRepertoireDir(const std::string &dir) { m_directory = dir; updateRepertoireList(); }

    public slots:
        void onDirectoryChanged();


    signals:
        void repertoireListChanged();

    private:
        std::string m_directory;
        std::string_view REPERTOIRE_FILE_EXTENSION = ".rep";

        QFileSystemWatcher m_watcher;

        std::unordered_map<std::string, Domain::Types::Repertoire::RepertoireData> m_cached_repertoires;
        std::vector<std::string> m_repertoire_list;
    };
}


#endif //CHESSREPO_REPERTOIRE_PERSISTENCE_H
