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
m_rep_controller(new repertoire_viewer::Controller(m_repertoire_service, this)),
      m_view(new EditPage(
          {
              m_board_controller->view(),
              m_explorer_controller->view(),
              m_rep_controller->view()
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
    connect(m_explorer_controller, &explorer::Controller::moveClicked,
            m_board_controller, &chessboard::Controller::makeUciMove);
    connect(m_rep_controller, &repertoire_viewer::Controller::moveClicked,
            m_board_controller, &chessboard::Controller::makeUciMove);
    connect(m_board_controller, &chessboard::Controller::boardChanged,
            m_explorer_controller, &explorer::Controller::exploreFen);
    connect(m_board_controller, &chessboard::Controller::boardChanged,
            m_rep_controller, &repertoire_viewer::Controller::getUciMovesForFEN);
    connect(m_rep_controller, &repertoire_viewer::Controller::requestMoveModels,
            m_board_controller, &chessboard::Controller::emitModelsFromUcis);
    connect(m_board_controller, &chessboard::Controller::convertedUcis,
            m_rep_controller, &repertoire_viewer::Controller::showMoves);
}
