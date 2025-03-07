//
// Created by Lecka on 04/03/2025.
//

#include "board_model.h"

#include <utility>


QVariant BoardModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            // Return column labels A-H
            return QString(QChar('A' + section));
        }
        if (orientation == Qt::Vertical) {
            // Return row labels 1-8
            return QString::number(8 - section);  // Invert rows (8 at the top)
        }
    }
    return {};
}

bool constexpr BoardModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    return false;
}

void BoardModel::show_moves_for_sq(chess::Square) {
}

QVariant BoardModel::data(const QModelIndex &index, const int role) const {
    if (!index.isValid()) {
        return {};
    }

    if (role == Qt::DisplayRole) {
        auto rank = chess::Rank(index.row());
        auto file = chess::File(index.column());
        auto square = chess::Square(rank, file);

        return static_cast<QVariant>(board.at(square));  // Return the piece at the given position
    }

    return {};
}

