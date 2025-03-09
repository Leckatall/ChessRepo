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
