//
// Created by Lecka on 04/03/2025.
//

#include "board_tblmodel.h"

#include <QColor>
#include <QDebug>

#include "domain/types/uci_move.h"

namespace chessboard {
    QVariant TblModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
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

    bool TblModel::setData(const QModelIndex &index, const QVariant &value, const int role) {
        emit dataChanged(index, index);
        return QAbstractTableModel::setData(index, value, role);
    }

    QVariant TblModel::data(const QModelIndex &index, int role) const {
        if (!index.isValid()) {
            return {};
        }
        if (role == Qt::DisplayRole) {
            const auto square = Board::square(index);
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

    Qt::ItemFlags TblModel::flags(const QModelIndex &index) const {
        Qt::ItemFlags flags = Qt::ItemIsEnabled;
        if (m_board.is_enabled_square(index)) {
            flags = flags | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
        } else {
            flags = flags | Qt::ItemIsDropEnabled;
        }
        return flags;
    }

    QSet<QModelIndex> TblModel::get_legal_targets_from(const QModelIndex &index) const {
        QSet<QModelIndex> targets = {};
        for (auto square: m_board.get_legal_targets_for(index)) {
            targets << square_to_index(square);
        }
        return targets;
    }

    void TblModel::emit_update() {
        emit dataChanged(createIndex(0, 0), createIndex(7, 7));
        emit boardUpdated();
    }

    void TblModel::try_select(const QModelIndex &index) {
        if (m_board.is_enabled_square(index)) {
            select(index);
        }
    }

    void TblModel::select(const QModelIndex &index) {
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

    void TblModel::target(const QModelIndex &index) {
        m_target_squares << index;
        auto square = data(index).value<SquareData>();
        square.isHighlighted = true;
        setData(index, QVariant::fromValue(square));
    }

    void TblModel::deselect(const QModelIndex &index) {
        auto square = data(index).value<SquareData>();
        square.isSelected = false;
        square.isHighlighted = false;
        setData(index, QVariant::fromValue(square));
    }

    void TblModel::clear_selection() {
        deselect(m_selected_square);
        m_selected_square = {};
        for (auto targ: m_target_squares) {
            deselect(targ);
        }
        m_target_squares = {};
    }

    void TblModel::try_move_to(const QModelIndex &index) {
        if (m_target_squares.contains(index)) {
            make_move(m_selected_square, index);
        }
    }

    template<typename... Args>
    void TblModel::makeMove(Args &&... args) {
        if (m_board.make_move(std::forward<Args>(args)...)) {
            emit_update();
        }
    }

    void TblModel::makeUciMove(const Domain::Types::UCIMove &uci) {
        // UCI format is like "e2e4" or "e7e8q" for promotion
        qDebug() << "Make UCI move in Model: " << uci;
        const auto move = chess::uci::uciToMove(m_board, uci);
        makeMove(move);
    }

    void TblModel::make_move(Models::Move m) {
        makeMove(m);
    }

    void TblModel::make_move(const QModelIndex &from, const QModelIndex &to) {
        makeMove(from, to);
    }

    void TblModel::undo_move() {
        if(m_board.undo_last_move()) {
            emit_update();
        }
    }
}
