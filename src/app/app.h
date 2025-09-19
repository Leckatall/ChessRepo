//
// Created by Lecka on 18/09/2025.
//

#ifndef CHESSREPO_APP_H
#define CHESSREPO_APP_H
#include <QMainWindow>

#include "controllers/board_controller.h"
#include "infrastructure/persistence/repertoire_persistence.h"
#include "presentation/models/explorer_tblmodel.h"
#include "presentation/viewmodels/explorer_viewmodel.h"
#include "ui/components/chessboard/board_view.h"
#include "ui/components/explorer/explorer_view.h"

namespace Application {
    class App: public QObject {
        Q_OBJECT
    public:
        App();
        void start() const;

    private:
        void initLayout() const;
        void initConnections();

        Infrastructure::Features::Explorer::LichessExplorerService m_lichessApi;
        Infrastructure::Features::Repertoire::RepertoirePersistence m_repertoirePersistence;

        QMainWindow *m_window;
        QFrame *m_container;
        Presentation::Features::Explorer::ExplorerViewModel m_explorerVM;
        chessboard::Controller *m_board_controller;
        explorer::View* m_explorerView;
    };
}



#endif //CHESSREPO_APP_H