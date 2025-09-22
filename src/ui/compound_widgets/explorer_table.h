//
// Created by Lecka on 22/09/2025.
//

#ifndef CHESSREPO_EXPLORER_TABLE_H
#define CHESSREPO_EXPLORER_TABLE_H
#include <QLabel>
#include <qtmetamacros.h>
#include <QWidget>

#include "components/explorer/explorer_tblview.h"
#include "types/uci_move.h"
#include "viewmodels/explorer_viewmodel.h"

namespace View::Features::Explorer {
    class ExplorerTable : public QWidget {
        Q_OBJECT

    public:
        explicit ExplorerTable(Presentation::Features::Explorer::ExplorerViewModel* view_model,
                               QWidget *parent = nullptr);

    signals:
        void moveIndexClicked(QModelIndex uci_move);

    public slots:
        void updatePositionStatsLabel() const;

    private:
        void initLayout();
        void initConnections();
        Presentation::Features::Explorer::ExplorerViewModel* m_viewModel;
        explorer::TblView *m_tblView;
        QLabel *m_current_pos_label;
    };
}


#endif //CHESSREPO_EXPLORER_TABLE_H
