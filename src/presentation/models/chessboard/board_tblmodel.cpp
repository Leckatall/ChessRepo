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
            const auto square = index_to_square(index);
            return QVariant::fromValue(SquareData(
                m_board.piece_at(square),
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
        if (m_board.is_enabled_square(index_to_square(index))) {
            flags = flags | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
        } else {
            flags = flags | Qt::ItemIsDropEnabled;
        }
        return flags;
    }

    void TblModel::set_state(const Domain::Features::Chess::Board &board) {
        m_board = board;
        emit_update();
    }

    void TblModel::emit_update() {
        emit dataChanged(createIndex(0, 0), createIndex(7, 7));
    }

    void TblModel::try_select(const QModelIndex &index) {
        if (m_board.is_enabled_square(index_to_square(index))) {
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
        for (auto target_square: m_board.get_legal_targets_from(index_to_square(index))) {
            target(square_to_index(target_square.toChessLib()));
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

}
