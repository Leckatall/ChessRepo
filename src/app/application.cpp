//
// Created by Lecka on 11/06/2025.
//

#include "application.h"

Application::Application(QWidget* parent) : QObject(parent) {
    m_router = new Router(parent);
    // m_openingController = new OpeningController(this);
    // m_repertoireService = new RepertoireService(this);

    setupConnections();
}

void Application::start() {
    m_router->display();
    m_router->show();
}

void Application::setupConnections() {
    // Example: When a repertoire is selected from list page
    // connect(m_router, &Router::pageChanged, this, [this](Router::Page page, const QVariantMap& params) {
    //     if (page == Router::Page::STUDY) {
    //         int repertoireId = params["repertoireId"].toInt();
    //         auto repertoire = m_repertoireService->getRepertoire(repertoireId);
    //         m_openingController->loadRepertoire(repertoire);
    //     }
    // });
}