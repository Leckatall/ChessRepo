//
// Created by Lecka on 11/06/2025.
//

#ifndef REPERTOIRE_CONTROLLER_H
#define REPERTOIRE_CONTROLLER_H
#include <QObject>

#include "Controller.h"


class RepertoireController : public Controller {
    Q_OBJECT

public:
    explicit RepertoireController(QObject *parent = nullptr): Controller(parent) {}

    QWidget* view(QWidget *parent = nullptr) override;
};


#endif //REPERTOIRE_CONTROLLER_H
