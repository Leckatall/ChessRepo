//
// Created by Lecka on 11/06/2025.
//

#include "application.h"

#include "controllers/edit_controller.h"

namespace application {
    Application::Application()
    : QObject(nullptr),
    m_window(new QMainWindow()),
    m_router(new Router()),
    m_repertoireService(new RepertoireService(this)),
    m_lichessApi(new LichessExplorerService(this))
    {
        m_window->setWindowTitle("ChessRepo");
        m_window->setGeometry(0, 0, 1200, 800);

        addView(Page::LIST, new RepertoireListController(this, m_router, m_repertoireService));
        addView(Page::EDIT, new EditController(this, m_router, m_repertoireService, m_lichessApi));
        // m_openingController = new OpeningController(this);
        // m_repertoireService = new RepertoireService(this);

        m_router->setContentsMargins(0, 0, 0, 0);
        m_router->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        m_window->setCentralWidget(m_router);

        initConnections();
    }

    void Application::addView(const Page page, Controller *controller) {
        m_controllers[page] = controller;
        m_router->addView(page, controller->view());
        connect(controller, &Controller::routeToPage, m_router, &Router::navigateTo);
    }

    void Application::updatePage(const Page page) {
        m_controllers[page]->updateView();
        m_router->update();
        m_router->updateGeometry();
    }

    void Application::start() const {
        m_router->navigateTo(Page::LIST);
        m_window->show();
    }

    void Application::initConnections() {
        connect(m_router, &Router::pageChanged,
                this, &Application::updatePage);
        connect(&m_repertoireService, &RepertoireService::repertoireListChanged,
                m_controllers[Page::LIST], &Controller::updateData);
        connect(&m_repertoireService, &RepertoireService::newRepertoireLoaded,
                m_controllers[Page::EDIT], &Controller::updateData);
    }
}
