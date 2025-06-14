//
// Created by Lecka on 13/06/2025.
//

#include "board_view.h"

namespace chessboard {
    View::View(QWidget *parent)
        : QWidget(parent),
          m_flip_btn(new QPushButton(this)),
          m_undo_btn(new QPushButton(this)),
          m_move_history_lbl(new QLabel(this)),
          m_tblView(new TblView(this)){
        m_flip_btn->setText("Flip board");
        m_undo_btn->setText("Undo move");
        auto* layout = new QVBoxLayout();

        layout->addWidget(m_tblView);
        layout->addWidget(m_move_history_lbl);
        layout->addWidget(m_flip_btn);
        layout->addWidget(m_undo_btn);
        setLayout(layout);
    }

    void View::setHistoryLabel(const QString &pgn_str) const {
        m_move_history_lbl->setText(pgn_str);
    }

    void View::initConnections() {
        connect(m_flip_btn, &QPushButton::clicked,
            this, [this]{ emit flipRequested();});
        connect(m_undo_btn, &QPushButton::clicked,
            this, [this]{ emit undoMoveRequested();});
        connect(m_tblView, &TblView::squareClicked,
                this, [this](QModelIndex index){ emit square_clicked(index);});
    }
} // chess_board
