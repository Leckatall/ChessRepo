//
// Created by Lecka on 04/04/2025.
//

#include "explorertblmodel.h"
#include "QMetaEnum"

const QMap<ExplorerTblModel::Column, QString> ExplorerTblModel::COLUMN_NAMES = {
    {MoveName, "Move"},
    {Popularity, "Popularity"},
    {Winrates, "Win Rates"},
    {Evaluation, "Evaluation"}
};

ExplorerTblModel::ExplorerTblModel(QObject *parent, const Qt::Orientation &orientation)
    : QAbstractTableModel(parent),
      m_orientation(orientation) {
}

QVariant ExplorerTblModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation != m_orientation) {
        return QString("Row %1").arg(section);
    }
    if(section < ColumnCount) {
        return COLUMN_NAMES[static_cast<Column>(section)];
    }
    return {};
}

int ExplorerTblModel::columnCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return ColumnCount;
}

int ExplorerTblModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return m_moves.size();
}

QVariant ExplorerTblModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_moves.size()) {
        return {};
    }
    const Models::MoveData &move = m_moves[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (static_cast<Column>(index.column())) {
            case MoveName:
                return move.san;
            case Popularity:
                return Models::formatPercentage(static_cast<double>(move.position_data.games) / static_cast<double>(m_root_position.games));
            case Winrates:
                return {};
            case Evaluation:
                return 0;
            case ColumnCount:
                break;
        }
    } else if (role == Qt::UserRole) {
        if(static_cast<Column>(index.column()) == Winrates) {
            return QVariant::fromValue(move.position_data);
        }
    } else if (role == Qt::ToolTipRole) {
        if(static_cast<Column>(index.column()) == Winrates) {
            return move.position_data.toToolTip();
        }
    }else if (role == Qt::TextAlignmentRole )
        return Qt::AlignCenter;

    return {};

}

void ExplorerTblModel::handleClick(const QModelIndex &index) {
    if (!index.isValid() || index.row() >= m_moves.size())
        return;

    emit moveClicked(m_moves[index.row()]);
}
