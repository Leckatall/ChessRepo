//
// Created by Lecka on 11/06/2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <qtmetamacros.h>
#include <QWidget>

#include "router.h"
#include "controllers/repertoire_controller.h"
#include "views/MainWindow.h"

namespace application {
    class Application : public QObject {
        Q_OBJECT

    public:
        explicit Application();

        void start();

    private slots:
        void updatePage(application::Page page);

    private:
        void addView(Page page, Controller* controller);

        void initConnections();

        QMainWindow* m_window;
        Router* m_router;
        QMap<Page, Controller*> m_controllers;
        OpeningService m_repertoireService;
    };
}

#endif //APPLICATION_H
