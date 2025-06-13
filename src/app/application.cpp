//
// Created by Lecka on 11/06/2025.
//

#include "application.h"

namespace application {
    Application::Application() : QObject(nullptr) {
        m_window = new QMainWindow();

        m_window->setWindowTitle("ChessRepo");
        m_window->setGeometry(0, 0, 1200, 800);

        m_router = new Router();


        addView(Page::LIST, new RepertoireController(this, m_router, m_repertoireService));
        // m_openingController = new OpeningController(this);
        // m_repertoireService = new RepertoireService(this);

        m_router->setContentsMargins(0, 0, 0, 0);
        m_router->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        m_window->setCentralWidget(m_router);

        initConnections();
    }

    void Application::addView(Page page, Controller *controller) {
        m_controllers[page] = controller;
        m_router->addView(page, controller->view());
    }

    void Application::updatePage(Page page) {
        m_controllers[page]->updateView();
        m_router->update();
        m_router->updateGeometry();
    }

    void Application::start() {
        m_router->navigateTo(Page::LIST);
        m_window->show();
    }

    void Application::initConnections() {
        connect(m_router, &Router::pageChanged,
                this, &Application::updatePage);
        connect(&m_repertoireService, &OpeningService::repertoireListChanged,
                m_controllers[Page::LIST], &Controller::updateData);
    }
}
