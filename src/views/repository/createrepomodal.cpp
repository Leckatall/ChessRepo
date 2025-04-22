//
// Created by Lecka on 21/04/2025.
//

#include "createrepomodal.h"

#include <QPushButton>

CreateRepoModal::CreateRepoModal(QWidget *parent)
    : QDialog(parent),
      m_layout(this),
      m_name_edit(this),
      m_desc_edit(this),
      m_auth_edit(this),
      m_for_white_check_box(this),
      m_button_box({QDialogButtonBox::Ok | QDialogButtonBox::Cancel}, this) {
    setWindowTitle("Create New Repertoire");
    initUI();
}


void CreateRepoModal::validateForm() const {
    m_button_box.button(QDialogButtonBox::Ok)->setEnabled(!m_name_edit.text().trimmed().isEmpty());
}

void CreateRepoModal::initUI() {
    const auto confirm_btn = m_button_box.button(QDialogButtonBox::Ok);
    confirm_btn->setText("Save");
    confirm_btn->setEnabled(false);
    confirm_btn->setDefault(true);

    m_name_edit.setPlaceholderText("Required");
    m_for_white_check_box.setChecked(true);

    m_layout.addRow("Name:", &m_name_edit);
    m_layout.addRow("Description:", &m_desc_edit);
    m_layout.addRow("Author:", &m_auth_edit);
    m_layout.addRow("For White:", &m_for_white_check_box);
    m_layout.addRow(&m_button_box);

    connect(&m_name_edit, QLineEdit::textChanged, this, validateForm);
    connect(&m_button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(&m_button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Models::OpeningRepertoire CreateRepoModal::getRepertoire() const {
    return {
        m_name_edit.text(),
        m_for_white_check_box.isChecked(),
        m_desc_edit.toPlainText(),
        m_auth_edit.text()
    };
}
