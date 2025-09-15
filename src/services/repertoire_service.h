#ifndef _REPERTOIRE_SERVICE_H
#define _REPERTOIRE_SERVICE_H


#include "LichessService.h"
#include "repertoire.h"

namespace Models { class FEN; } 

class RepertoireService : public typedef37 {
  Q_OBJECT
  public:
    inline explicit RepertoireService(QObject * parent = nullptr) : QObject(parent) {
            updateRepertoireList();
    
            // Monitors the repertoire directory for any changes
            m_watcher.addPath(getRepoDir());
            connect(&m_watcher, &QFileSystemWatcher::directoryChanged,
                    this, &RepertoireService::onDirectoryChanged);
        };

    QStringList get_repertoire_list();

    inline Models::Repertoire get_current_repertoire() { return m_current_repertoire; };

    QList<Models::Move> get_moves_from_fen(const Models::FEN & fen);

    void load_repertoire(const QString & name);

  public slots:    bool saveRepertoire(const Models::Repertoire & rep);

    Models::Repertoire getRepertoire(const QString & name);

  signals:    void repertoireListChanged();

    void repertoireChanged(const QString & _t1);

    void newRepertoireLoaded();

    void error(const QString & _t1);

  private slots:
  private:
    void onDirectoryChanged();

    static QString getRepoDir();

    static QString getRepertoireFilePath(const QString & name);

    void updateRepertoireList();

    Models::Repertoire read_repertoire_file(const QString & name);

    Models::Repertoire m_current_repertoire;

    QHash<QString,Models::Repertoire> m_cache;

    QStringList m_repertoire_title_list;

    QFileSystemWatcher m_watcher;

};
#endif
