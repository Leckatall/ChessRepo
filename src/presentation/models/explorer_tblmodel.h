//
// Created by Lecka on 04/04/2025.
//

#ifndef EXPLORERTBLMODEL_H
#define EXPLORERTBLMODEL_H
#include <QAbstractTableModel>
#include <utility>

#include "domain/types/position/position_graph.h"
#include "infrastructure/explorer/lichess_request_builder.h"

namespace Domain::Types {
    class UCIMove;
    struct PositionStats;
}

namespace Presentation::Features::Explorer {
    class TableModel : public QAbstractTableModel {
        Q_OBJECT

    public:
        enum Column {
            MoveName = 0,
            Popularity,
            Winrates,
            Evaluation,
            ColumnCount
        };

        Q_ENUM(Column);

        explicit TableModel(QObject *parent = nullptr, const Qt::Orientation &orientation = Qt::Horizontal);

        [[nodiscard]] QVariant
        headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

        [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        void setGraph(const Domain::Types::PositionGraph& graph);

    public slots:
            void handleClick(const QModelIndex &index);

        signals:
            void moveClicked(const Domain::Types::UCIMove &move);

    private:
        Qt::Orientation m_orientation;
        static const QMap<Column, QString> COLUMN_NAMES;
        struct RowEntry {
            Domain::Types::UCIMove uci_move;
            Domain::Types::PositionStats stats;
        };
        Domain::Types::PositionStats m_root_stats;
        Domain::Types::FEN m_root_FEN;
        QList<RowEntry> m_moves;
    };
}



#endif //EXPLORERTBLMODEL_H
