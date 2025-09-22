//
// Created by Lecka on 18/09/2025.
//

#ifndef CHESSREPO_APP_H
#define CHESSREPO_APP_H
#include <QMainWindow>

#include "compound_widgets/chessboard_table.h"
#include "compound_widgets/explorer_table.h"
#include "compound_widgets/repertoire_manager_widget.h"
#include "infrastructure/persistence/repertoire_persistence.h"
#include "models/explorer_tblmodel.h"
#include "viewmodels/explorer_viewmodel.h"
#include "ui/components/chessboard/board_view.h"
#include "viewmodels/board_viewmodel.h"

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
        Presentation::Features::Repertoire::RepertoireViewModel m_repertoireVM;
        Domain::Features::Chess::Board m_board;
        Presentation::Features::Board::BoardTableViewModel m_boardVM;
        View::Features::Explorer::ExplorerTable* m_explorerView;
        View::Features::Repertoire::RepertoireManagerWidget* m_repertoireManagerWidget;
        View::Features::Board::ChessboardTable *m_boardTable;
    };
}



#endif //CHESSREPO_APP_H