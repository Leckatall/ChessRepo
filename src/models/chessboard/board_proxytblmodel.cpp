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

    QModelIndex ProxyTblModel::mapToSource(const QModelIndex &proxyIndex) const {
        if (!proxyIndex.isValid())
            return {};
        int row = proxyIndex.row();
        if (m_white_on_bottom) {
            row = sourceModel()->rowCount() - 1 - proxyIndex.row();
        }
        return sourceModel()->index(row, proxyIndex.column());
    }

    QModelIndex ProxyTblModel::square_to_index(const chess::Square square) const {
        //TODO: Refactor this to 1 line
        if (!sourceModel()) {
            return {};
        }

        int sourceRow = 7 - square.rank();
        int column = square.file();

        int viewRow = m_white_on_bottom ? sourceRow : (7 - sourceRow);

        return index(viewRow, column);
    }
}
