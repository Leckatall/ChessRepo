//
// Created by Lecka on 11/06/2025.
//

#include "repertoire_controller.h"

#include "services/OpeningService.h"
#include "ui/pages/list/repotoirelist_page.h"



void RepertoireController::updateView() {
    if(m_is_view_outdated) {
        m_view->updateRepertoireList(m_repertoire_list);
        m_is_view_outdated = false;
    }
}

void RepertoireController::updateData() {
    m_repertoire_list = m_repertoire_service.get_repertoire_list();
    m_is_view_outdated = true;
}
