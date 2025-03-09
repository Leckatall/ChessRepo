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
#include "models/tablemodel.h"
#include "services/LichessService.h"
#include "views/boardtblview.h"


class ExplorerController : public QObject {
    Q_OBJECT

public:
    explicit ExplorerController(QWidget *parent = nullptr);


    [[nodiscard]] QFrame *view() const;

    void update_model(const QList<QMap<QString, QVariant>>& new_data);

public slots:
    void handleMoveClicked(const QModelIndex &index);

    void exploreFen(const QString &fen);

    void updatePositionData(const LichessService::PositionData& position);

    void updateMoves(QList<LichessService::MoveData> moves);

private:
    void initUI();
    void initConnections();
    static const QStringList TABLE_HEADERS;
    QFrame *m_container;
    QVBoxLayout m_layout;
    ExplorerTblView m_table_view;
    QLabel m_current_pos_label;
    TableModel m_table_model;
    LichessService m_lichess_api;
};


#endif //EXPLORERCONTROLLER_H
