//
// Created by Lecka on 11/03/2025.
//

#include "winratedelegate.h"

#include <QLabel>
#include <QPainter>
#include <QPainterPath>

#include "models/datatypes.h"

void WinrateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    const auto pos_data = index.data(Qt::UserRole).value<Models::PositionData>();

    auto widths = calculate_widths(option.rect.width(), pos_data);

    const QRect rect_w = option.rect.adjusted(PADDING, PADDING, -option.rect.width() + widths.white + PADDING, -PADDING);
    const QRect rect_d = option.rect.adjusted(widths.white, PADDING, -option.rect.width() + widths.white + widths.draw, -PADDING);
    const QRect rect_b = option.rect.adjusted(option.rect.width() - widths.black - PADDING, PADDING, -PADDING, -PADDING);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    QPainterPath path_w;
    path_w.addRoundedRect(rect_w, RADIUS, RADIUS);
    painter->fillPath(path_w, QColor(255, 255, 255));

    QPainterPath path_b;
    path_b.addRoundedRect(rect_b, RADIUS, RADIUS);
    painter->fillPath(path_b, QColor(0, 0, 0));

    QPainterPath path_d;
    path_d.addRect(rect_d);
    painter->fillPath(path_d, QColor(150, 150, 150));

    painter->setPen(Qt::black);
    painter->drawText(rect_w, Qt::AlignCenter, QString::number(pos_data.white_wr() * 100, 'g', 4) + "%");
    painter->setPen(Qt::white);
    if (pos_data.draw_rate() > 0.03) {
        painter->drawText(rect_d, Qt::AlignCenter, QString::number(pos_data.draw_rate() * 100, 'g', 4) + "%");
    }
    painter->drawText(rect_b, Qt::AlignCenter, QString::number(pos_data.black_wr() * 100, 'g', 4) + "%");

    painter->restore();

    QStyledItemDelegate::paint(painter, option, index);
}

QSize WinrateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(option, index);
}


