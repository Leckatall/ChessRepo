//
// Created by Lecka on 07/03/2025.
//

#include "boardcontroller.h"
#include <QDebug>

#include "views/squaredelegate.h"


BoardController::BoardController(QWidget *parent)
    : QObject(parent),
      m_container(new QFrame(parent)),
      m_layout(m_container),
      m_boardTblView(m_container),
      m_boardTblModel(this),
      m_boardProxyModel(this) {
    initUI();
    initConnections();
}

QWidget *BoardController::view() const {
    return m_container;
}

QString BoardController::get_current_fen() const {
    return m_boardTblModel.get_fen();
}

void BoardController::handleSquareClicked(const QModelIndex &proxy_index) {
    auto index = m_boardProxyModel.mapToSource(proxy_index);
    m_boardTblModel.begin_update();
    if (m_boardTblModel.square_selected()) {
        // A piece has already been selected
        m_boardTblModel.try_move_to(index);
        emit boardChanged(m_boardTblModel.get_fen());
        // Clear the currrent highlights:
        // Case A: they're moving and they no longer apply
        // Case B: They're changing the piece to move and they no longer apply
        m_boardTblModel.clear_selection();
    }
    m_boardTblModel.try_select(index);
    m_boardTblModel.end_update();
}

void BoardController::initUI() {
    m_boardProxyModel.setSourceModel(&m_boardTblModel);
    m_boardTblView.setModel(&m_boardProxyModel);

    m_layout.addWidget(&m_boardTblView);
    m_container->setLayout(&m_layout);
}

void BoardController::initConnections() {
    connect(&m_boardTblView, &BoardTblView::squareClicked,
            this, &BoardController::handleSquareClicked);
}
