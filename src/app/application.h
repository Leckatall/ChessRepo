#ifndef APPLICATION_APPLICATION_H
#define APPLICATION_APPLICATION_H


#include "models.h"
#include "repertoire_service.h"
#include "LichessService.h"

class Controller;
namespace application { class Router; } 
namespace chessboard { class Controller; } 
namespace explorer { class Controller; } 

namespace application {

typedef QObject typedef24;
class Application : public typedef24 {
  Q_OBJECT
  public:
    explicit Application();

    void start() const;

  private slots:
  private:
    void updatePage(Page page);

    void addView(Page page, ::Controller * controller);

    void initConnections();

    QMainWindow * m_window;

    Router * m_router;

    ::RepertoireService m_repertoireService;

    ::LichessService m_lichessApi;

    QMap<Page,Controller*> m_controllers;

    chessboard::Controller * m_board_controller;

    explorer::Controller * m_explorer_controller;

};

} // namespace application
#endif
