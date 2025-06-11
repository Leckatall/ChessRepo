//
// Created by Lecka on 06/04/2025.
//

#include "openingcontroller.h"

#include "views/repertoires/createrepomodal.h"

OpeningController::OpeningController(QWidget *parent)
    : QObject(parent),
      m_container(new QFrame(parent)),
      m_layout(m_container),
      m_opener_select(m_container),
      m_load_opener_btn("Load Opener", m_container),
      m_save_opener_btn("Save Opener", m_container),
      m_add_line_btn("Add Line", m_container),
      m_opening_service(this),
      m_openers(getOpeners() << m_add_opener_selection) {
    initUI();
    initConnections();
}

void OpeningController::initUI() {
    m_container->setFrameStyle(QFrame::Box);

    m_opener_select.setPlaceholderText("No repo selected");
    update_combo_box();
    m_opener_select.setCurrentIndex(-1);

    m_layout.addWidget(&m_opener_select, 0, 0, 1, 2);
    m_layout.addWidget(&m_load_opener_btn, 0, 2);
    m_layout.addWidget(&m_save_opener_btn, 1, 0);
    m_layout.addWidget(&m_add_line_btn, 1, 1);
    m_container->setLayout(&m_layout);
}

void OpeningController::initConnections() {
    connect(&m_opener_select, &QComboBox::currentIndexChanged,
            this, selectedOpenerChanged);
}

void OpeningController::update_combo_box() {
    const QSignalBlocker blocker(m_opener_select);

    m_opener_select.clear();
    m_opener_select.addItems(m_openers);

    // Restore selection
    if (const int index = m_opener_select.findText(m_current_repo.name); index >= 0) {
        m_opener_select.setCurrentIndex(index);
    }
}

QWidget *OpeningController::view() const {
    return m_container;
}

QList<Models::UCIMove> OpeningController::responses_for_pos(const Models::FEN &pos) {
    return m_current_repo.positions[pos].responses.keys();
}

void OpeningController::saveRepo() {
    m_opening_service.saveRepertoire(m_current_repo);
}

void OpeningController::selectedOpenerChanged(const int new_index) {
    if (new_index == m_opener_select.count() - 1) {
        // Create new repo
        createRepo();
        update_combo_box();
        return;
    }
    m_current_repo = m_opening_service.getRepertoire(m_opener_select.currentText());
}

QList<QString> OpeningController::getOpeners() {
    return OpeningService::list_repertoires();
}

void OpeningController::annotateForPosition(Models::FEN pos) {
}

bool OpeningController::createRepo() {
    if (const auto modal = new CreateRepoModal(m_container); modal->exec() == QDialog::Accepted) {
        m_current_repo = modal->getRepertoire();
        saveRepo();
        return true;
    }
    return false;
}
