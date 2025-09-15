//
// Created by Lecka on 13/06/2025.
//

#ifndef EDIT_CONTROLLER_H
#define EDIT_CONTROLLER_H
#include "Controller.h"
#include "repertoire_viewer_controller.h"
#include "services/repertoire_service.h"
#include "ui/pages/edit/edit_page.h"

class EditController : public Controller {
    Q_OBJECT

public:
    explicit EditController(application::Application *app,
        QWidget *router_widget,
        RepertoireService &rep_service,
        LichessService &lichess_service);

    [[nodiscard]] QWidget *view() const override { return m_view; }

public slots:
    void updateView() override;

    void updateData() override;

    void add_current_line();

    // void onEditRequest(QString rep_name);

private:
    void initConnections();
    RepertoireService &m_repertoire_service;
    Models::Repertoire m_current_repertoire;
    chessboard::Controller *m_board_controller;
    explorer::Controller *m_explorer_controller;
    repertoire_viewer::Controller *m_rep_controller;
    EditPage *m_view;

    bool m_is_view_outdated{true};
};

#endif //EDIT_CONTROLLER_H
