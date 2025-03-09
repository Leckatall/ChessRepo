//
// Created by Lecka on 07/03/2025.
//

#include "boardcontroller.h"
#include <QDebug>

#include "views/squaredelegate.h"


BoardController::BoardController(QObject *parent)
    : m_boardTblModel(new BoardTblModel(this)),
      m_boardProxyModel(new BoardTblProxyModel(this)),
      m_boardTblView(new BoardTblView()) {
    m_boardProxyModel->setSourceModel(m_boardTblModel);
    m_boardTblView->setModel(m_boardProxyModel);

    connect(m_boardTblView, &BoardTblView::squareClicked,
            this, &BoardController::handleSquareClicked);
}

BoardTblView *BoardController::tbl_view() const {
    return m_boardTblView;
}

void BoardController::handleSquareClicked(const QModelIndex &proxy_index) const {
    auto index = m_boardProxyModel->mapToSource(proxy_index);
    m_boardTblModel->begin_update();
    if (m_boardTblModel->square_selected()) {
        // A piece has already been selected
        m_boardTblModel->try_move_to(index);
        // Clear the currrent highlights:
        // Case A: they're moving and they no longer apply
        // Case B: They're changing the piece to move and they no longer apply
        m_boardTblModel->clear_selection();
    }
    m_boardTblModel->try_select(index);
    m_boardTblModel->end_update();
}
