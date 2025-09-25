//
// Created by Lecka on 24/09/2025.
//

#include "repertoire_selection_widget.h"

#include <QGridLayout>
#include <QLabel>

#include "components/createrepomodal.h"

namespace View::Features::Persistence {
    RepertoireSelectionWidget::RepertoireSelectionWidget(
    Presentation::Features::Persistence::RepertoireSelectionViewmodel *viewmodel, QWidget *parent)
    : QFrame(parent),
      m_viewmodel(viewmodel) {
        m_selectedRepertoireComboBox = new QComboBox(this);
        m_selectedRepertoireComboBox->addItems(m_viewmodel->getRepertoireList());
        m_selectedRepertoireComboBox->setPlaceholderText("Select a Repertoire");
        m_deleteRepBtn = new QPushButton("Delete Repertoire", this);
        m_saveRepBtn = new QPushButton("Save Repertoire", this);
        m_editRepHeadBtn = new QPushButton("Edit Header", this);
        m_newRepBtn = new QPushButton("New Repertoire", this); //TODO: just put this as an option of CB
        initLayout();
        initConnections();
    }

    void RepertoireSelectionWidget::saveCurrentRepertoire() const {
        m_viewmodel->saveRepertoire();
    }

    void RepertoireSelectionWidget::initLayout() {
        // ReSharper disable once CppDFAMemoryLeak
        auto *layout = new QGridLayout(this);
        layout->addWidget(new QLabel("Repertoire Selection", this), 0, 0, 1, 3, Qt::AlignCenter);
        layout->addWidget(m_selectedRepertoireComboBox, 1, 1);
        layout->addWidget(m_saveRepBtn, 2, 0);
        layout->addWidget(m_deleteRepBtn, 2, 2);
        layout->addWidget(m_editRepHeadBtn, 3, 0);
        layout->addWidget(m_newRepBtn, 3, 1);

        this->setLayout(layout);
    }

    void RepertoireSelectionWidget::initConnections() {
        connect(m_selectedRepertoireComboBox, &QComboBox::currentTextChanged,
            m_viewmodel, &Presentation::Features::Persistence::RepertoireSelectionViewmodel::selectRepertoire);
        connect(m_saveRepBtn, &QPushButton::clicked,
            this, &RepertoireSelectionWidget::saveCurrentRepertoire);
    }

    void RepertoireSelectionWidget::editRepertoireHeader() {
        auto rep_data = m_viewmodel->getRepertoireData();
        Repertoire::RepertoireHeaderModal modal(rep_data.header, this);
        if (modal.exec() == QDialog::Accepted) {
            m_viewmodel->editRepertoireHeader(modal.getHeader());
        }
    }

    void RepertoireSelectionWidget::createNewRepertoire() {
        Repertoire::RepertoireHeaderModal modal(this);
        if (modal.exec() == QDialog::Accepted) {
            m_viewmodel->createNewRepertoire(modal.getHeader());
        }
    }
}
