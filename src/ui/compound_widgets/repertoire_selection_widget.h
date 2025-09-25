//
// Created by Lecka on 24/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_SELECTION_WIDGET_H
#define CHESSREPO_REPERTOIRE_SELECTION_WIDGET_H
#include <QCheckBox>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>

#include "viewmodels/repertoire_selection_viewmodel.h"

namespace View::Features::Persistence {
    class RepertoireSelectionWidget: public QFrame {
        Q_OBJECT
    public:
        explicit RepertoireSelectionWidget(Presentation::Features::Persistence::RepertoireSelectionViewmodel* viewmodel, QWidget *parent = nullptr);

    private slots:
        void saveCurrentRepertoire() const;

    private:
        void initLayout();
        void initConnections();
        void editRepertoireHeader();
        void createNewRepertoire();
        Presentation::Features::Persistence::RepertoireSelectionViewmodel* m_viewmodel;
        QComboBox* m_selectedRepertoireComboBox;
        QPushButton* m_loadRepBtn;
        QPushButton* m_deleteRepBtn;
        QPushButton* m_saveRepBtn;
        QPushButton* m_editRepHeadBtn;
        QPushButton* m_newRepBtn;
    };
}



#endif //CHESSREPO_REPERTOIRE_SELECTION_WIDGET_H