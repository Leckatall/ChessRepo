//
// Created by Lecka on 11/06/2025.
//

#ifndef REPERTOIRE_CONTROLLER_H
#define REPERTOIRE_CONTROLLER_H
#include <QObject>

#include "Controller.h"
#include "services/OpeningService.h"
#include "ui/pages/list/repotoirelist_page.h"


class RepertoireController : public Controller {
    Q_OBJECT

public:
    explicit RepertoireController(application::Application *app, QWidget *router_widget, OpeningService &service)
        : Controller(app),
          m_repertoire_service(service),
          m_repertoire_list(m_repertoire_service.get_repertoire_list()),
          m_view(new RepertoireListPage(router_widget)) {
    }

    [[nodiscard]] QWidget *view() const override { return m_view; }

public slots:
    void updateView() override;

    void updateData() override;

private:
    OpeningService &m_repertoire_service;
    QStringList m_repertoire_list;
    RepertoireListPage *m_view;
    bool m_is_view_outdated{true};
};


#endif //REPERTOIRE_CONTROLLER_H
