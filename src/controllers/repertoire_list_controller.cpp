//
// Created by Lecka on 11/06/2025.
//

#include "repertoire_list_controller.h"


RepertoireListController::RepertoireListController(application::Application *app, QWidget *router_widget,
                                                   RepertoireService &service)
    : Controller(app),
      m_repertoire_service(service),
      m_repertoire_list(m_repertoire_service.get_repertoire_list()),
      m_view(new ListPage(router_widget)) {
    initConnections();
}

void RepertoireListController::initConnections() {
    connect(m_view, &ListPage::createRequested, this, &RepertoireListController::onCreateRequest);
    connect(m_view, &ListPage::deleteRequested, this, &RepertoireListController::onDeleteRequest);
    connect(m_view, &ListPage::studyRequested, this, &RepertoireListController::onStudyRequest);
    connect(m_view, &ListPage::editRequested, this, &RepertoireListController::onEditRequest);
}


void RepertoireListController::updateView() {
    if (m_is_view_outdated) {
        m_view->updateRepertoireList(m_repertoire_list);
        m_is_view_outdated = false;
    }
}

void RepertoireListController::updateData() {
    m_repertoire_list = m_repertoire_service.get_repertoire_list();
    m_is_view_outdated = true;
}

void RepertoireListController::onCreateRequest() {
    qDebug() << "Create requested";
}

void RepertoireListController::onDeleteRequest(QString rep_name) {
    qDebug() << "Delete of " << rep_name << " requested";
}

void RepertoireListController::onStudyRequest(QString rep_name) {
    qDebug() << "Study of " << rep_name << " requested";
}

void RepertoireListController::onEditRequest(const QString& rep_name) {
    m_repertoire_service.load_repertoire(rep_name);
    qDebug() << "Routing to Edit page of " << rep_name << " requested";
    emit routeToPage(application::Page::EDIT);
}


