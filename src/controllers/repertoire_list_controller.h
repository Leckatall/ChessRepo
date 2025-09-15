//
// Created by Lecka on 11/06/2025.
//

#ifndef REPERTOIRE_CONTROLLER_H
#define REPERTOIRE_CONTROLLER_H

#include "Controller.h"
#include "app/models.h"
#include "services/repertoire_service.h"
#include "ui/pages/list/list_page.h"


class RepertoireListController : public Controller {
    Q_OBJECT

public:
    explicit RepertoireListController(application::Application *app, QWidget *router_widget,
                                      RepertoireService &service);

    [[nodiscard]] QWidget *view() const override { return m_view; }

public slots:
    void updateView() override;

    void updateData() override;

    void onCreateRequest();

    void onStudyRequest(QString rep_name);

    void onEditRequest(const QString &rep_name);

    void onDeleteRequest(QString rep_name);

private:
    void initConnections();

    RepertoireService &m_repertoire_service;
    QStringList m_repertoire_list;
    ListPage *m_view;
    bool m_is_view_outdated{true};
};


#endif //REPERTOIRE_CONTROLLER_H
