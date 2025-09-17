//
// Created by Lecka on 11/06/2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <qtmetamacros.h>
#include <QWidget>
#include <QMainWindow>

#include "router.h"
#include "controllers/board_controller.h"
#include "controllers/explorer_controller.h"
#include "controllers/repertoire_list_controller.h"
#include "infrastructure/explorer/lichess_service.h"
#include "ui/components/explorer/explorer_view.h"

namespace application {
    class Application : public QObject {
        Q_OBJECT

    public:
        explicit Application();

        void start() const;

    private slots:
        void updatePage(application::Page page);

    private:
        void addView(Page page, Controller* controller);

        void initConnections();

        QMainWindow* m_window;
        Router* m_router;

        RepertoireService m_repertoireService;
        Infrastructure::Explorer::LichessExplorerService m_lichessApi;

        QMap<Page, Controller*> m_controllers;
        chessboard::Controller* m_board_controller;
        explorer::Controller* m_explorer_controller;

    };
}

#endif //APPLICATION_H
