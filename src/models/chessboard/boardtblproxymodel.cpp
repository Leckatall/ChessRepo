//
// Created by Lecka on 09/03/2025.
//

#include "boardtblproxymodel.h"

QModelIndex BoardTblProxyModel::mapFromSource(const QModelIndex &sourceIndex) const {
    if (!sourceIndex.isValid())
        return {};

    int row = sourceIndex.row();
    if(m_white_on_bottom) {
        row = sourceModel()->rowCount() - 1 - sourceIndex.row();
    }
    return createIndex(row, sourceIndex.column(), sourceIndex.internalPointer());
}

QModelIndex BoardTblProxyModel::mapToSource(const QModelIndex &proxyIndex) const {
    if (!proxyIndex.isValid())
        return {};
    int row = proxyIndex.row();
    if(m_white_on_bottom) {
        row = sourceModel()->rowCount() - 1 - proxyIndex.row();
    }
    return sourceModel()->index(row, proxyIndex.column());
}

QModelIndex BoardTblProxyModel::square_to_index(chess::Square square) {
    //TODO: Refactor this to 1 line
    if (!sourceModel()) {
        return {};
    }

    int sourceRow = 7 - square.rank();
    int column = square.file();

    int viewRow = m_white_on_bottom ? sourceRow : (7 - sourceRow);

    return index(viewRow, column);
}
