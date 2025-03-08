//
// Created by Lecka on 07/03/2025.
//

#include "boardcontroller.h"
#include <QDebug>


BoardController::BoardController(BoardTblModel *model, BoardTblView *view, QObject *parent)
    : m_boardTblModel(model),
      m_boardTblView(view) {
    connect(m_boardTblView, &BoardTblView::squareClicked,
        this, &BoardController::handleSquareClicked);
}

void BoardController::handleSquareClicked(const QModelIndex &index) {
    if (m_selected_square.isValid()) {
        // A piece has already been selected
        // Clear the currrent highlights:
            // Case A: they're moving and they no longer apply
            // Case B: They're changing the piece to move and they no longer apply
        m_boardTblModel->deselect(m_selected_square);
        for (auto target: m_targeted_squares) {
            m_boardTblModel->deselect(target);
        }
        if(m_targeted_squares.contains(index)) {
            m_boardTblModel->make_move(m_selected_square, index);
            m_targeted_squares.clear();
            m_boardTblModel->update_selections(m_selected_square, m_targeted_squares);
            return;
        }
        m_targeted_squares.clear();
    }
    m_selected_square = index;
    m_boardTblModel->select(m_selected_square);
    m_targeted_squares = m_boardTblModel->get_legal_targets_from(m_selected_square);
    for(auto target: m_targeted_squares) {
        m_boardTblModel->target(target);
    }
    m_boardTblModel->update_selections(m_selected_square, m_targeted_squares);
}


