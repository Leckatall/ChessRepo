//
// Created by Lecka on 22/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_MANAGER_WIDGET_H
#define CHESSREPO_REPERTOIRE_MANAGER_WIDGET_H
#include <QPushButton>
#include <QWidget>

#include "components/repertoire/moves_deck.h"
#include "viewmodels/repertoire_viewmodel.h"

namespace View::Features::Repertoire {
    class RepertoireManagerWidget: public QWidget {
        Q_OBJECT
    public:
        explicit RepertoireManagerWidget(Presentation::Features::Repertoire::RepertoireViewModel* view_model, QWidget *parent = nullptr);

        signals:
        void addLineRequested();

    private:
        void initLayout();
        void initConnections();

        Presentation::Features::Repertoire::RepertoireViewModel* m_viewModel;
        MovesDeck* m_deck;
        QPushButton* m_add_line_btn;
    };
}



#endif //CHESSREPO_REPERTOIRE_MANAGER_WIDGET_H