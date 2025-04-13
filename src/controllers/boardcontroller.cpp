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
      m_flip_btn(m_container),
      m_undo_btn(m_container),
      m_boardTblView(m_container),
      m_boardTblModel(this),
      m_boardProxyModel(this),
      m_arrow_overlay(&m_boardTblView) {
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

void BoardController::makeUciMove(const QString &uci) {
    m_boardTblModel.makeUciMove(uci);
    emit boardChanged(m_boardTblModel.get_fen());
    m_boardTblModel.clear_selection();
}

void BoardController::flipBoard() {
    m_boardProxyModel.flip();
}

void BoardController::undoMove() {
    m_boardTblModel.undo_move();
    emit boardChanged(m_boardTblModel.get_fen());
}

void BoardController::initUI() {
    m_flip_btn.setText("Flip board");
    m_undo_btn.setText("Undo move");

    m_boardProxyModel.setSourceModel(&m_boardTblModel);
    m_boardTblView.setModel(&m_boardProxyModel);

    m_layout.addWidget(&m_boardTblView);
    m_layout.addWidget(&m_flip_btn);
    m_layout.addWidget(&m_undo_btn);
    m_container->setLayout(&m_layout);

    auto arrow_from = m_boardProxyModel.square_to_index(chess::Square("b1"));
    auto arrow_to = m_boardProxyModel.square_to_index(chess::Square("c3"));
    m_arrow_overlay.add_arrow({arrow_from, arrow_to});

    // arrow_from = m_boardProxyModel.square_to_index(chess::Square("g1"));
    // arrow_to = m_boardProxyModel.square_to_index(chess::Square("f3"));
    // m_arrow_overlay.add_arrow({arrow_from, arrow_to});
    // arrow_from = m_boardProxyModel.square_to_index(chess::Square("b8"));
    // arrow_to = m_boardProxyModel.square_to_index(chess::Square("c6"));
    // m_arrow_overlay.add_arrow({arrow_from, arrow_to});
    // arrow_from = m_boardProxyModel.square_to_index(chess::Square("g8"));
    // arrow_to = m_boardProxyModel.square_to_index(chess::Square("f6"));
    // m_arrow_overlay.add_arrow({arrow_from, arrow_to});
}

void BoardController::initConnections() {
    connect(&m_flip_btn, &QPushButton::clicked, this, &BoardController::flipBoard);
    connect(&m_undo_btn, &QPushButton::clicked, this, &BoardController::undoMove);
    connect(&m_boardTblView, &BoardTblView::squareClicked,
            this, &BoardController::handleSquareClicked);
}
