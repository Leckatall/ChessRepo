
#include "board_proxytblmodel.h"

namespace chessboard {

QModelIndex ProxyTblModel::mapFromSource() const {

        if (!sourceIndex.isValid())
            return {};

        int row = sourceIndex.row();
        if (m_white_on_bottom) {
            row = sourceModel()->rowCount() - 1 - sourceIndex.row();
        }
        return createIndex(row, sourceIndex.column(), sourceIndex.internalPointer());
}

QModelIndex ProxyTblModel::mapToSource() const {

        if (!proxyIndex.isValid())
            return {};
        int row = proxyIndex.row();
        if (m_white_on_bottom) {
            row = sourceModel()->rowCount() - 1 - proxyIndex.row();
        }
        return sourceModel()->index(row, proxyIndex.column());
}


} // namespace chessboard
