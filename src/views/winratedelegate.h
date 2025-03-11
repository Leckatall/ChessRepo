//
// Created by Lecka on 11/03/2025.
//

#ifndef WINRATEDELEGATE_H
#define WINRATEDELEGATE_H
#include <QStyledItemDelegate>


class WinrateDelegate : public QStyledItemDelegate {
public:
    explicit WinrateDelegate(QObject *parent = nullptr): QStyledItemDelegate(parent) {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};



#endif //WINRATEDELEGATE_H
