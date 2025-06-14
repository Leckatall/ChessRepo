//
// Created by Lecka on 13/06/2025.
//

#ifndef BOARD_VIEW_H
#define BOARD_VIEW_H
#include <qboxlayout.h>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "board_tblview.h"
#include "models/chessboard/board_proxytblmodel.h"

namespace chessboard {
    class View : public QWidget {
        Q_OBJECT

    public:
        explicit View(QWidget *parent = nullptr);

        void setTblModel(QAbstractItemModel *model) const {m_tblView->setModel(model);}

        void setHistoryLabel(const QString &pgn_str) const;

    signals:
        void square_clicked(QModelIndex proxy_index);

        void flipRequested();

        void undoMoveRequested();

    private:
        void initConnections();

        QPushButton *m_flip_btn;
        QPushButton *m_undo_btn;
        QLabel *m_move_history_lbl;
        TblView *m_tblView;
    };
} // chess_board

#endif //BOARD_VIEW_H
