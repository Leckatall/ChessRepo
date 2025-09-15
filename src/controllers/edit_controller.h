#ifndef _EDIT_CONTROLLER_H
#define _EDIT_CONTROLLER_H


#include "Controller.h"
#include "repertoire.h"

namespace application { class Application; } 
class RepertoireService;
class LichessService;
namespace chessboard { class Controller; } 
namespace explorer { class Controller; } 
namespace repertoire_viewer { class Controller; } 
class EditPage;

class EditController : public Controller {
  Q_OBJECT
  public:
    explicit EditController(application::Application * app, QWidget * router_widget, RepertoireService & rep_service, LichessService & lichess_service);

    inline QWidget * view() const override { return m_view; };

  public slots:    void updateView() override;

    void updateData() override;

    void add_current_line();


  private:
    // void onEditRequest(QString rep_name);
    void initConnections();

    RepertoireService & m_repertoire_service;

    Models::Repertoire m_current_repertoire;

    chessboard::Controller * m_board_controller;

    explorer::Controller * m_explorer_controller;

    repertoire_viewer::Controller * m_rep_controller;

    EditPage * m_view;

    bool m_is_view_outdated {true};

};
#endif
