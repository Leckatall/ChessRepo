//
// Created by Lecka on 11/06/2025.
//

#include "router.h"

#include "ui/pages/list/list_page.h"

namespace application {
    Router::Router(QWidget *parent): QStackedWidget(parent) {
    }

    void Router::navigateTo(const Page page) {
        auto* page_view = m_pages.value(page);
        if (!page_view) {
            qDebug() << "No view registered for page" << static_cast<int>(page);
            return;
        }
        setCurrentWidget(page_view);

        emit pageChanged(page);
    }

    void Router::addView(const Page page, QWidget *view) {
        view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        addWidget(view);
        m_pages[page] = view;
    }

    // void Router::goBack() {
    //     if (!canGoBack()) return;
    //
    //     // Remove current page
    //     auto* current = this->currentWidget();
    //     this->removeWidget(current);
    //     delete current;
    //
    //     // Go back to previous
    //     m_history.pop();
    //     const auto prevState = m_history.top();
    //     display(prevState);
    // }
    //
    // bool Router::canGoBack() const {
    //     return true;
    // }
}

