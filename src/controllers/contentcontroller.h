//
// Created by Lecka on 09/03/2025.
//

#ifndef CONTENTCONTROLLER_H
#define CONTENTCONTROLLER_H
#include <QFrame>
#include <QObject>


class ContentController: public QObject {
    Q_OBJECT

public:
    explicit ContentController(QObject *parent = nullptr): QObject(parent) {}
    ~ContentController() override {
        delete m_container;
    }
    virtual QFrame* view() {return m_container ? m_container : m_container = new QFrame();}
    virtual void update_model() {}
private:
    QFrame* m_container = {};
};



#endif //CONTENTCONTROLLER_H
