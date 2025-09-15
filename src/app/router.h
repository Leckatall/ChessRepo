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

#include "models.h"


namespace application {
    class Router : public QStackedWidget {
        Q_OBJECT

    public:
        explicit Router(QWidget *parent = nullptr);

        void navigateTo(Page page);

        void addView(Page page, QWidget* view);

    signals:
        void pageChanged(application::Page);

    private:
        QMap<Page, QWidget*> m_pages;
    };
}


#endif //ROUTER_H
