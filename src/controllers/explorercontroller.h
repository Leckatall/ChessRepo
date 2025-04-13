//
// Created by Lecka on 09/03/2025.
//

#ifndef EXPLORERCONTROLLER_H
#define EXPLORERCONTROLLER_H
#include <QGridLayout>
#include <QObject>
#include <QStringList>
#include <QLabel>
#include <views/explorertblview.h>

#include "contentcontroller.h"
#include "models/explorertblmodel.h"
#include "models/tablemodel.h"
#include "services/LichessService.h"
#include "views/boardtblview.h"


class ExplorerController : public QObject {
    Q_OBJECT

public:
    explicit ExplorerController(QWidget *parent = nullptr);

    [[nodiscard]] QFrame *view() const;

public slots:
    void handleMoveClicked(const Models::MoveData &move);

    void exploreFen(const QString &fen);

    void updatePositionData(const Models::PositionData &position);

    void updateMoves(const QList<Models::MoveData> &moves);

signals:
    void moveClicked(QString uci);

private:
    void initUI();

    void initConnections();

    QFrame *m_container;
    QVBoxLayout m_layout;
    ExplorerTblView m_table_view;
    QLabel m_current_pos_label;
    ExplorerTblModel m_table_model;
    LichessService m_lichess_api;

    Models::PositionData m_current_position{};
};


#endif //EXPLORERCONTROLLER_H
