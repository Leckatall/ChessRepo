//
// Created by Lecka on 11/06/2025.
//

#include "router.h"

#include "services/OpeningService.h"
#include "ui/pages/list/repotoirelist_page.h"


void Router::display(const Route route) {
    // QWidget* page_view = m_page_controllers[route.page]->view(this);
    // if (!page_view) return;
    QWidget* page_view = m_repertoire_controller.view(this);
    if (!page_view) {
        qDebug() << "Widget is null!";
        return;
    }
    this->addWidget(page_view);
    this->setCurrentWidget(page_view);

    emit pageChanged(route);
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
