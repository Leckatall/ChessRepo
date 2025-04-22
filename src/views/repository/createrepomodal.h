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

#include "models/datatypes.h"

class CreateRepoModal: public QDialog {
Q_OBJECT
    // TODO: Don't allow creation of repos with names that already exist
public:
    explicit CreateRepoModal(QWidget* parent = nullptr);

    Models::OpeningRepertoire getRepertoire() const;

private slots:
    void validateForm() const;

private:
    void initUI();
    QFormLayout m_layout;
    QLineEdit m_name_edit;
    QTextEdit m_desc_edit;
    QLineEdit m_auth_edit;
    QCheckBox m_for_white_check_box;
    QDialogButtonBox m_button_box;
};



#endif //CREATEREPOMODAL_H
