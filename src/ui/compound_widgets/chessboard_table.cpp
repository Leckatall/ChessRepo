//
// Created by Lecka on 22/09/2025.
//

#include "chessboard_table.h"

#include <QGridLayout>

#include "viewmodels/board_table_viewmodel.h"


namespace View::Features::Board {
    ChessboardTable::ChessboardTable(Presentation::Features::Board::BoardTableViewModel *view_model, QWidget *parent)
        : QWidget(parent),
          m_view_model(view_model),
          m_flip_btn(new QPushButton("Flip", this)),
          m_undo_btn(new QPushButton("Undo", this)),
          m_move_history_lbl(new QLabel("MoveHistoryLabel", this)),
          m_tblView(new chessboard::TblView(this)) {
        m_tblView->setModel(m_view_model->boardProxyModel());
        initLayout();
        initConnections();
    }

    void ChessboardTable::setHistoryLabel(const QString &pgn_str) const {
        m_move_history_lbl->setText(pgn_str);
    }


    void ChessboardTable::initLayout() {
        // ReSharper disable once CppDFAMemoryLeak
        const auto layout = new QGridLayout(this);
        m_tblView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_move_history_lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_flip_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_undo_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addWidget(m_tblView, 0, 0, 1, 2);
        layout->addWidget(m_flip_btn, 1, 0);
        layout->addWidget(m_undo_btn, 1, 1);
        layout->addWidget(m_move_history_lbl, 2, 0, 1, 2);
        layout->setRowStretch(0, 5); // tblView: Tall
        layout->setRowStretch(1, 0); // buttons: Short
        layout->setRowStretch(2, 1); // move history: Medium

        layout->setColumnStretch(0, 1);
        layout->setColumnStretch(1, 1);
        layout->setColumnStretch(2, 1);
        setLayout(layout);
    }

    void ChessboardTable::initConnections() {
        connect(m_flip_btn, &QPushButton::clicked,
                m_view_model, &Presentation::Features::Board::BoardTableViewModel::flipBoard);
        connect(m_undo_btn, &QPushButton::clicked,
                m_view_model, &Presentation::Features::Board::BoardTableViewModel::undoMove);
        connect(m_tblView, &chessboard::TblView::squareClicked,
                m_view_model, &Presentation::Features::Board::BoardTableViewModel::handleSquareClicked);
    }
}
