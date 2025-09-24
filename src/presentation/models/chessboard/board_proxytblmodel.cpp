//
// Created by Lecka on 09/03/2025.
//

#include "board_proxytblmodel.h"

namespace chessboard {
    QModelIndex ProxyTblModel::mapFromSource(const QModelIndex &sourceIndex) const {
        if (!sourceIndex.isValid())
            return {};

        int row = sourceIndex.row();
        if (m_white_on_bottom) {
            row = sourceModel()->rowCount() - 1 - sourceIndex.row();
        }
        return createIndex(row, sourceIndex.column(), sourceIndex.internalPointer());
    }

    Domain::Types::Chess::Square ProxyTblModel::sourceIndexToSquare(const QModelIndex &sourceIndex) const {
        if (!sourceIndex.isValid()) return {};

        return {sourceIndex.column(), m_white_on_bottom ? sourceIndex.row() : 7 - sourceIndex.row()};
    }

    QModelIndex ProxyTblModel::mapToSource(const QModelIndex &proxyIndex) const {
        if (!proxyIndex.isValid())
            return {};
        int row = proxyIndex.row();
        if (m_white_on_bottom) {
            row = sourceModel()->rowCount() - 1 - proxyIndex.row();
        }
        return sourceModel()->index(row, proxyIndex.column());
    }


    QModelIndex ProxyTblModel::squareToIndex(const Domain::Types::Chess::Square square) const {
        if (!sourceModel()) return {};

        return index(m_white_on_bottom ? 7 - square.rank() : square.rank(), square.file());
    }
}
