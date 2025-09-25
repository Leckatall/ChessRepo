//
// Created by Lecka on 21/04/2025.
//

#ifndef CREATEREPOMODAL_H
#define CREATEREPOMODAL_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>

#include "repertoire/repertoire.h"

namespace View::Features::Repertoire {
    class RepertoireHeaderModal: public QDialog {
        Q_OBJECT
            // TODO: Don't allow creation of repos with names that already exist
        public:
        explicit RepertoireHeaderModal(QWidget* parent = nullptr);
        explicit RepertoireHeaderModal(const Domain::Types::Repertoire::Header &rep_header, QWidget* parent = nullptr);

        [[nodiscard]] Domain::Types::Repertoire::Header getHeader() const;

    private slots:
        void validateForm() const;

    private:
        void initUI();

        std::optional<Domain::Types::Repertoire::Header> m_rep_header;
        QFormLayout m_layout;
        QLineEdit m_name_edit;
        QTextEdit m_desc_edit;
        QLineEdit m_auth_edit;
        QCheckBox m_for_white_check_box;
        QDialogButtonBox m_button_box;
    };
}




#endif //CREATEREPOMODAL_H
