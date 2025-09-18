//
// Created by Lecka on 04/04/2025.
//

#include "explorer_tblmodel.h"
#include "QMetaEnum"
#include "presentation/uitls.h"
#include "presentation/viewmodels/explorer_viewmodel.h"

namespace Presentation::Features::Explorer {
    const QMap<TableModel::Column, QString> TableModel::COLUMN_NAMES = {
    {MoveName, "Move"},
    {Popularity, "Popularity"},
    {Winrates, "Win Rates"},
    {Evaluation, "Evaluation"}
};

TableModel::TableModel(QObject *parent, const Qt::Orientation &orientation)
    : QAbstractTableModel(parent),
      m_orientation(orientation), m_root_FEN(Domain::Types::FEN::startingPosition()) {
}

QVariant TableModel::headerData(int section, const Qt::Orientation orientation, const int role) const {
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

int TableModel::columnCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return ColumnCount;
}

int TableModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return m_moves.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_moves.size()) {
        return {};
    }
    const auto &[uci_move, stats] = m_moves[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (static_cast<Column>(index.column())) {
            case MoveName:
                return uci_move;
            case Popularity:
                return Presentation::Utils::toPercentage(stats.games, m_root_stats.games);
            case Winrates:
                return {};
            case Evaluation:
                return 0;
            case ColumnCount:
                break;
        }
    } else if (role == Qt::UserRole) {
        if(static_cast<Column>(index.column()) == Winrates) {
            return QVariant::fromValue(stats);
        }
    } else if (role == Qt::TextAlignmentRole )
        return Qt::AlignCenter;

    return {};

}

void TableModel::setGraph(const Domain::Types::PositionGraph &graph) {
    beginResetModel();
    const auto root_node = graph.getNode(graph.getRootKey());
    m_root_FEN = root_node->getFen();
    m_root_stats = root_node->stats;
    const auto move_edges = root_node->edges;
    m_moves.clear();
    m_moves.reserve(move_edges.size());
    for (const auto &edge : move_edges) {
        m_moves.push_back(RowEntry{QString::fromStdString(edge.uci), graph.getStats(edge)});
    }
    endResetModel();
    emit dataChanged(createIndex(0, 0),
                     createIndex(rowCount() - 1, columnCount() - 1));
}

void TableModel::handleClick(const QModelIndex &index) {
    if (!index.isValid() || index.row() >= m_moves.size())
        return;

    emit moveClicked(Domain::Types::UCIMove(m_moves[index.row()].uci_move.toStdString()));
}
}

