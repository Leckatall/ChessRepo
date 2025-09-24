//
// Created by Lecka on 24/09/2025.
//

#include "repertoire_selection_widget.h"

#include <QGridLayout>
#include <QLabel>

namespace View::Features::Persistence {
    RepertoireSelectionWidget::RepertoireSelectionWidget(
    Presentation::Features::Persistence::RepertoireSelectionViewmodel *viewmodel, QWidget *parent)
    : QFrame(parent),
      m_viewmodel(viewmodel) {
        m_repDescriptionEdit = new QTextEdit(this);
        m_repForWhiteCheckBox = new QCheckBox(this);
        m_selectedRepertoireComboBox = new QComboBox(this);
        m_selectedRepertoireComboBox->addItems(m_viewmodel->loadRepertoireList());
        m_selectedRepertoireComboBox->setPlaceholderText("Select Repertoire");
        m_loadRepBtn = new QPushButton("Load Repertoire", this);
        m_deleteRepBtn = new QPushButton("Delete Repertoire", this);
        m_saveRepBtn = new QPushButton("Save Repertoire", this);
        initLayout();
        initConnections();
    }

    void RepertoireSelectionWidget::saveCurrentRepertoire() const {
        Domain::Types::Repertoire::RepertoireData repertoire = m_viewmodel->getRepertoireData(m_viewmodel->getSelectedRepertoireName());
        repertoire.header.description = m_repDescriptionEdit->toPlainText().toStdString();
        repertoire.header.forWhite = m_repForWhiteCheckBox->isChecked();
        m_viewmodel->saveRepertoire(repertoire);
    }

    void RepertoireSelectionWidget::initLayout() {
        // ReSharper disable once CppDFAMemoryLeak
        auto *layout = new QGridLayout(this);
        layout->addWidget(new QLabel("Repertoire Selection", this), 0, 0);
        layout->addWidget(m_selectedRepertoireComboBox, 1, 0);
        layout->addWidget(m_saveRepBtn, 2, 0);
        layout->addWidget(m_loadRepBtn, 2, 1);
        layout->addWidget(m_deleteRepBtn, 2, 2);
        layout->addWidget(m_repForWhiteCheckBox, 2, 3);
        layout->addWidget(m_repDescriptionEdit, 3, 0);
        this->setLayout(layout);
    }

    void RepertoireSelectionWidget::initConnections() {
        connect(m_selectedRepertoireComboBox, &QComboBox::currentTextChanged,
            m_viewmodel, &Presentation::Features::Persistence::RepertoireSelectionViewmodel::selectRepertoire);
        connect(m_saveRepBtn, &QPushButton::clicked,
            this, &RepertoireSelectionWidget::saveCurrentRepertoire);
    }

}
