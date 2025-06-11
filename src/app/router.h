//
// Created by Lecka on 11/06/2025.
//

#ifndef ROUTER_H
#define ROUTER_H
#include <qboxlayout.h>
#include <QMap>
#include <QStack>
#include <QStackedWidget>
#include <QObject>

#include "controllers/Controller.h"
#include "controllers/repertoire_controller.h"

enum class Page {
    LIST,
    STUDY,
    EDIT
};

struct Route {
    Page page;
    const QVariantMap &params = {};
    Route(const Page pg, const QVariantMap &params = {}): page(pg), params(params) {}
};

class Router : public QStackedWidget {
    Q_OBJECT

public:
    explicit Router(QWidget *parent = nullptr): QStackedWidget(parent), m_repertoire_controller(this) {
        setWindowTitle("ChessRepo");
        setGeometry(0, 0, 1200, 800);
        m_page_controllers = {{Page::LIST, new RepertoireController(this)}};
    }

    void display(Route route = {Page::LIST});

    void goBack();

    [[nodiscard]] bool canGoBack() const;

signals:
    void pageChanged(Route);

private:
    QWidget* requestPage(Page page);

    QStack<Route> m_history{};
    QMap<Page, Controller*> m_page_controllers;
    RepertoireController m_repertoire_controller;
};


#endif //ROUTER_H
