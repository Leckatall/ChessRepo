//
// Created by Lecka on 09/03/2025.
//

#ifndef BOARDTBLPROXYMODEL_H
#define BOARDTBLPROXYMODEL_H

#include <chess.hpp>
#include <QSortFilterProxyModel>

#include "chess/primitives.h"

namespace chessboard {
    class ProxyTblModel : public QSortFilterProxyModel {
    public:
        explicit ProxyTblModel(QObject *parent = nullptr): QSortFilterProxyModel(parent), m_white_on_bottom(true) {
        }

        [[nodiscard]] QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
        Domain::Types::Chess::Square sourceIndexToSquare(const QModelIndex &sourceIndex) const;

        [[nodiscard]] QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
        [[nodiscard]] QModelIndex squareToIndex(Domain::Types::Chess::Square square) const;

        void flip() {
            m_white_on_bottom = !m_white_on_bottom;
            invalidate();
        }

    private:
        bool m_white_on_bottom;
    };
}



#endif //BOARDTBLPROXYMODEL_H
