//
// Created by Lecka on 04/03/2025.
//

#include "boardtblmodel.h"

#include <QColor>
#include <QDebug>


QVariant BoardTblModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            // Return column labels A-H
            return QString(QChar('A' + section));
        }
        if (orientation == Qt::Vertical) {
            // Return row labels 1-8
            return QString::number(8 - section); // Invert rows (8 at the top)
        }
    }
    return {};
}

bool BoardTblModel::setData(const QModelIndex &index, const QVariant &value, const int role) {
    return QAbstractTableModel::setData(index, value, role);
}

QVariant BoardTblModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return {};
    }
    if (role == Qt::DisplayRole) {
        const auto square = BoardWrapper::square(index);
        return QVariant::fromValue(SquareData(
            m_board.at(square),
            square.is_light(),
            m_selected_square == index,
            m_targeted_squares.contains(index)));
    }
    return {};
}

Qt::ItemFlags BoardTblModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    if (m_board.is_enabled_square(index)) {
        flags = flags | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
    } else {
        flags = flags | Qt::ItemIsDropEnabled;
    }
    return flags;
}

QSet<QModelIndex> BoardTblModel::get_legal_targets_from(const QModelIndex &index) const {
    QSet<QModelIndex> targets = {};
    for (auto square: m_board.get_legal_targets_for(index)) {
        targets << square_to_index(square);
    }
    qDebug() << targets;
    return targets;
}

void BoardTblModel::select(const QModelIndex &index) {
    auto square = data(index).value<SquareData>();
    square.isSelected = true;
    setData(index, QVariant::fromValue(square));
}

void BoardTblModel::target(const QModelIndex &index) {
    auto square = data(index).value<SquareData>();
    square.isHighlighted = true;
    setData(index, QVariant::fromValue(square));
}

void BoardTblModel::deselect(const QModelIndex &index) {
    auto square = data(index).value<SquareData>();
    square.isSelected = false;
    square.isHighlighted = false;
    setData(index, QVariant::fromValue(square));
}

void BoardTblModel::update_selections(const QModelIndex &sel, const QSet<QModelIndex> &targets) {
    qDebug() << "Targeted squares: ";
    for(auto target: m_targeted_squares) {
        qDebug() << "Index row:" << target.row() << ", column:" << target.column();
    }
    m_selected_square = sel;
    m_targeted_squares = targets;
    emit dataChanged(createIndex(0, 0), createIndex(7, 7));
}

void BoardTblModel::make_move(const QModelIndex &from, const QModelIndex &to) {
    m_board.make_move(from, to);
}

void BoardTblModel::undo_move(const QModelIndex &from, const QModelIndex &to) {
    m_board.undo_move(from, to);
}
