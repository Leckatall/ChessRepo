//
// Created by Lecka on 11/06/2025.
//

#include "repertoire_controller.h"

#include "services/OpeningService.h"
#include "ui/pages/list/repotoirelist_page.h"

QWidget * RepertoireController::view(QWidget *parent) {
    // const auto page = ;
    // page->showRepertoireList(OpeningService::list_repertoires());
    return new RepertoireListPage(parent);
}
