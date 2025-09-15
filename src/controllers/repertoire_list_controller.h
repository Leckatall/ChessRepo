#ifndef _REPERTOIRE_LIST_CONTROLLER_H
#define _REPERTOIRE_LIST_CONTROLLER_H


#include "Controller.h"

namespace application { class Application; } 
class RepertoireService;
class ListPage;

class RepertoireListController : public Controller {
  Q_OBJECT
  public:
    explicit RepertoireListController(application::Application * app, QWidget * router_widget, RepertoireService & service);

    inline QWidget * view() const override { return m_view; };

  public slots:    void updateView() override;

    void updateData() override;

    void onCreateRequest();

    void onStudyRequest(QString rep_name);

    void onEditRequest(const QString & rep_name);

    void onDeleteRequest(QString rep_name);


  private:
    void initConnections();

    RepertoireService & m_repertoire_service;

    QStringList m_repertoire_list;

    ListPage * m_view;

    bool m_is_view_outdated {true};

};
#endif
