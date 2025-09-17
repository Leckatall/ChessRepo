//
// Created by Lecka on 04/04/2025.
//

#ifndef EXPLORERTBLMODEL_H
#define EXPLORERTBLMODEL_H
#include <QAbstractTableModel>
#include <utility>

#include "../../models/datatypes.h"
#include "tablemodel.h"

namespace explorer {
    class TblModel : public QAbstractTableModel {
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

        explicit TblModel(QObject *parent = nullptr, const Qt::Orientation &orientation = Qt::Horizontal);

        [[nodiscard]] QVariant
        headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

        [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        void put_data(const QList<Models::MoveData> &moves) {
            beginResetModel();
            m_moves = moves;
            endResetModel();
            emit dataChanged(createIndex(0, 0),
                             createIndex(rowCount() - 1, columnCount() - 1));
        }

        void set_root_position(const Models::PositionData &root_position) {
            m_root_position = root_position;
        }

        public slots:
            void handleClick(const QModelIndex &index);

        signals:
            void moveClicked(const Models::MoveData &move);

    private:
        Qt::Orientation m_orientation;
        static const QMap<Column, QString> COLUMN_NAMES;
        QList<Models::MoveData> m_moves;
        Models::PositionData m_root_position;
    };
}



#endif //EXPLORERTBLMODEL_H
