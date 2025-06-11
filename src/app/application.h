//
// Created by Lecka on 11/06/2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <qtmetamacros.h>
#include <QWidget>

#include "router.h"
#include "controllers/openingcontroller.h"
#include "controllers/repertoire_controller.h"


class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QWidget* parent = nullptr);
    void start();

private:
    Router* m_router;
    OpeningController* m_openingController;
    RepertoireController* m_repertoireController;

    void setupConnections();
};



#endif //APPLICATION_H
