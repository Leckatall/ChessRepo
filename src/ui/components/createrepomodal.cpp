//
// Created by Lecka on 21/04/2025.
//

#include "createrepomodal.h"

#include <qdatetime.h>
#include <QPushButton>

namespace View::Features::Repertoire {
    RepertoireHeaderModal::RepertoireHeaderModal(QWidget *parent)
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

    RepertoireHeaderModal::RepertoireHeaderModal(const Domain::Types::Repertoire::Header &rep_header, QWidget *parent)
        : RepertoireHeaderModal(parent) {
        m_rep_header = rep_header;
        m_name_edit.setText(QString::fromStdString(m_rep_header->name));
        m_name_edit.setReadOnly(true);
        m_desc_edit.setText(QString::fromStdString(m_rep_header->description));
        m_auth_edit.setText(QString::fromStdString(m_rep_header->author));
        m_for_white_check_box.setChecked(m_rep_header->forWhite);
        validateForm();
    }


    void RepertoireHeaderModal::validateForm() const {
        m_button_box.button(QDialogButtonBox::Ok)->setEnabled(!m_name_edit.text().trimmed().isEmpty());
    }

    void RepertoireHeaderModal::initUI() {
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

        connect(&m_name_edit, &QLineEdit::textChanged, this, &RepertoireHeaderModal::validateForm);
        connect(&m_button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(&m_button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    Domain::Types::Repertoire::Header RepertoireHeaderModal::getHeader() const {
        return Domain::Types::Repertoire::Header{
            m_name_edit.text().toStdString(),
            m_desc_edit.toPlainText().toStdString(),
            m_auth_edit.text().toStdString(),
            m_for_white_check_box.isChecked(),
            m_rep_header
                ? m_rep_header->createdAt
                : std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>(
                    std::chrono::sys_seconds::duration{QDateTime::currentSecsSinceEpoch()}),
        };
    }
}
