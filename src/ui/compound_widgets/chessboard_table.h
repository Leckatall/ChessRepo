//
// Created by Lecka on 22/09/2025.
//

#ifndef CHESSREPO_CHESSBOARD_TABLE_H
#define CHESSREPO_CHESSBOARD_TABLE_H
#include <QLabel>
#include <QPushButton>
#include <qtmetamacros.h>
#include <QWidget>

#include "components/chessboard/board_tblview.h"
#include "viewmodels/board_table_viewmodel.h"

namespace View::Features::Board {
    class ChessboardTable : public QWidget {
        Q_OBJECT

    public:
        explicit ChessboardTable(Presentation::Features::Board::BoardTableViewModel *view_model,
                                 QWidget *parent = nullptr);

    public slots:
        void setHistoryLabel(const QString &pgn_str) const;

    private:
        void initLayout();

        void initConnections();

        Presentation::Features::Board::BoardTableViewModel *m_view_model;
        QPushButton *m_flip_btn;
        QPushButton *m_undo_btn;
        QLabel *m_move_history_lbl;
        chessboard::TblView *m_tblView;
    };
}

#endif //CHESSREPO_CHESSBOARD_TABLE_H
