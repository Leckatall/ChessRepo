//
// Created by Lecka on 09/03/2025.
//

#include "explorercontroller.h"

#include "models/tablemodel.h"
#include "views/boardtblview.h"

#include <QGridLayout>

const QStringList ExplorerController::TABLE_HEADERS = {"A", "B", "C", "D"};

ExplorerController::ExplorerController(QWidget *parent)
    : QObject(parent),
      m_container(new QFrame(parent)),
      m_layout(m_container),
      m_table_view(m_container),
      m_current_pos_label(m_container),
      m_table_model(TABLE_HEADERS, parent),
      m_lichess_api(this) {
    initUI();
    initConnections();
}

void ExplorerController::initUI() {
    m_table_view.setModel(&m_table_model);

    m_container->setFrameStyle(QFrame::Box);
    m_current_pos_label.setStyleSheet("QLabel { color: white; font-weight: bold; }");
    m_current_pos_label.setText("Placeholder");
    m_layout.addWidget(&m_table_view);
    m_layout.addWidget(&m_current_pos_label);
    m_container->setLayout(&m_layout);
}

void ExplorerController::initConnections() {
    connect(&m_lichess_api, &LichessService::gotPositionData,
            this, &ExplorerController::updatePositionData);
    connect(&m_lichess_api, &LichessService::gotMovesData,
            this, &ExplorerController::updateMoves);
}

QFrame *ExplorerController::view() const {
    return m_container;
}

void ExplorerController::update_model(const QList<QMap<QString, QVariant> > &new_data) {
    // m_table_model.update_data(new_data);
}

void ExplorerController::handleMoveClicked(const QModelIndex &index) {
}

void ExplorerController::exploreFen(const QString &fen) {
    // will emit signals to connected to: updatePositionData(pos) and updateMoves(moves)
    m_lichess_api.fetch_opening_data(fen);
}

void ExplorerController::updatePositionData(const LichessService::PositionData &position) {
    QString new_text = "Games: " + QString::number(position.games) +
                       "\nWhite Wins: " + QString::number(position.white_wins) +
                       "\nDraws: " + QString::number(position.draws) +
                       "\nBlack Wins: " + QString::number(position.black_wins);
    if (position.opening) {
        new_text += "\nOpening(name:" + position.opening.name + " eco: " + position.opening.eco + ")";
    }
    m_current_pos_label.setText(new_text);
}

void ExplorerController::updateMoves(QList<LichessService::MoveData> moves) {
}
