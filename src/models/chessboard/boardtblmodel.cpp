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
            return QString::number(section + 1);
        }
    }
    return {};
}

bool BoardTblModel::setData(const QModelIndex &index, const QVariant &value, const int role) {
    emit dataChanged(index, index);
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
            m_target_squares.contains(index)));
    }
    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
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
    return targets;
}

void BoardTblModel::emit_update() {
    emit dataChanged(createIndex(0, 0), createIndex(7, 7));
}

void BoardTblModel::try_select(const QModelIndex &index) {
    if (m_board.is_enabled_square(index)) {
        select(index);
    }
}

void BoardTblModel::select(const QModelIndex &index) {
    // Select clicked square
    m_selected_square = index;
    auto square = data(index).value<SquareData>();
    square.isSelected = true;
    setData(index, QVariant::fromValue(square));

    // Target all the legal target squares
    m_target_squares.clear();
    for (auto target_square: m_board.get_legal_targets_for(index)) {
        target(square_to_index(target_square));
    }
}

void BoardTblModel::target(const QModelIndex &index) {
    m_target_squares << index;
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


void BoardTblModel::clear_selection() {
    deselect(m_selected_square);
    m_selected_square = {};
    for (auto targ: m_target_squares) {
        deselect(targ);
    }
    m_target_squares = {};
}

void BoardTblModel::try_move_to(const QModelIndex &index) {
    if (m_target_squares.contains(index)) {
        make_move(m_selected_square, index);
    }
}

void BoardTblModel::makeUciMove(const QString &uci) {
    // UCI format is like "e2e4" or "e7e8q" for promotion
    const auto move = chess::uci::uciToMove(m_board, uci.toStdString());
    m_board.makeMove(move);
    emit_update();
}

void BoardTblModel::updateMoveHistory(const Models::Move& m) {
    m_move_history.append(m);
}

void BoardTblModel::make_move(Models::Move m) {
    emit madeMove(m_board.make_move(m));
    emit_update();
}
void BoardTblModel::make_move(const QModelIndex &from, const QModelIndex &to) {
    emit madeMove(m_board.make_move(from, to));
    emit_update();
}

void BoardTblModel::undo_move() {
    if (m_move_history.empty()) { return; }
    const auto move = m_move_history.takeLast();
    m_board.undo_move(move);
    emit_update();
}
