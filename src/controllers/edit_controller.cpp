//
// Created by Lecka on 13/06/2025.
//

#include "edit_controller.h"

#include "app/models.h"
#include "QDebug"

EditController::EditController(application::Application *app,
                               QWidget *router_widget,
                               RepertoireService &rep_service,
                               LichessService &lichess_service)
    : Controller(app),
      m_repertoire_service(rep_service),
      m_board_controller(new chessboard::Controller(this)),
      m_explorer_controller(new explorer::Controller(lichess_service, this)),
      m_view(new EditPage(
          {
              m_board_controller->view(),
              m_explorer_controller->view()
          },
          router_widget)) {
    initConnections();
}

void EditController::updateView() {
    if (m_is_view_outdated) {
        m_view->set_repertoire(m_current_repertoire);
        m_is_view_outdated = false;
    }
}

void EditController::updateData() {
    if (const auto new_repertoire = m_repertoire_service.get_current_repertoire();
        m_current_repertoire != new_repertoire) {
        m_is_view_outdated = true;
        m_current_repertoire = new_repertoire;
    }
}

void EditController::initConnections() {
    connect(m_view, &EditPage::routeToListRequested,
            this, [this] { emit routeToPage(application::Page::LIST); });
    connect(m_view, &EditPage::uciMoveRequest,
            m_board_controller, &chessboard::Controller::makeUciMove);
    connect(m_view, &EditPage::explorerUpdateRequested, m_view, &EditPage::updateExplorer);

}
