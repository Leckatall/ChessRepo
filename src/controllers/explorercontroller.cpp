//
// Created by Lecka on 09/03/2025.
//

#include "explorercontroller.h"

#include "models/tablemodel.h"
#include "views/boardtblview.h"

#include <QGridLayout>
#include <QString>


ExplorerController::ExplorerController(QWidget *parent)
    : QObject(parent),
      m_container(new QFrame(parent)),
      m_layout(m_container),
      m_table_view(m_container),
      m_current_pos_label(m_container),
      m_table_model(parent),
      m_lichess_api(this) {
    initUI();
    initConnections();
}

void ExplorerController::initUI() {
    m_table_view.setModel(&m_table_model);
    m_table_view.initUI();

    m_container->setFrameStyle(QFrame::Box);
    m_current_pos_label.setStyleSheet("QLabel { color: white; font-weight: bold; }");
    m_current_pos_label.setText("Placeholder");
    m_layout.addWidget(&m_table_view);
    m_layout.addWidget(&m_current_pos_label);
    m_container->setLayout(&m_layout);
}

void ExplorerController::initConnections() {
    // Updating the model
    connect(&m_lichess_api, &LichessService::gotPositionData,
            this, &ExplorerController::updatePositionData);
    connect(&m_lichess_api, &LichessService::gotMovesData,
            this, &ExplorerController::updateMoves);
    // Handling table clicks
    connect(&m_table_view, &QTableView::clicked,
            &m_table_model, &ExplorerTblModel::handleClick);
    connect(&m_table_model, &ExplorerTblModel::moveClicked,
            this, &ExplorerController::handleMoveClicked);
}

QFrame *ExplorerController::view() const {
    return m_container;
}

void ExplorerController::handleMoveClicked(const Models::MoveData& move) {
    emit moveClicked(move.uci);
}

void ExplorerController::exploreFen(const QString &fen) {
    // will emit signals to connected to: updatePositionData(pos) and updateMoves(moves)
    m_lichess_api.fetch_opening_data(fen);
}

void ExplorerController::updatePositionData(const Models::PositionData &position) {
    m_current_position = position;
    QString new_text = "Games: " + QString::number(position.games) +
                       "\nWhite Wins: " + QString::number(position.white_wins) +
                       "\nDraws: " + QString::number(position.draws) +
                       "\nBlack Wins: " + QString::number(position.black_wins);
    if (position.opening) {
        new_text += QString("\nOpening(name: \"%1\" eco: \"%2\")").arg(position.opening.name, position.opening.eco);
    }
    m_current_pos_label.setText(new_text);
    m_table_model.set_root_position(position);
}

void ExplorerController::updateMoves(const QList<Models::MoveData> &moves) {
    m_table_model.put_data(moves);
}
