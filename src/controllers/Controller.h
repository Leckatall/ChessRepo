//
// Created by Lecka on 11/06/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>


class Controller: public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr): QObject(parent) {}
    virtual QWidget* view(QWidget *parent = nullptr) = 0;
};


#endif //CONTROLLER_H
