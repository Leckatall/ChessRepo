//
// Created by Lecka on 11/03/2025.
//

#include "winratedelegate.h"

#include <QLabel>
#include <QPainter>
#include <QPainterPath>

void WinrateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    auto values = index.data().toList();
    if(values.size() != 3) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    int total = values[0].toInt() + values[1].toInt() + values[2].toInt();
    if (total ==0) {
        // Do smth
    }

    double white_wr = values[0].toDouble() / total;

    double draw_rate = values[1].toDouble() / total;

    double black_wr = values[2].toDouble() / total;

    int width_w = static_cast<int>(option.rect.width() * white_wr);
    int width_b = static_cast<int>(option.rect.width() * black_wr);
    int width_d = option.rect.width() - width_w - width_b;

    int padding = 5;
    int radius = 5;

    QRect rect_w = option.rect.adjusted(padding, padding, -option.rect.width() + width_w + padding, -padding);
    QRect rect_d = option.rect.adjusted(width_w, padding, -option.rect.width() + width_w + width_d, -padding);
    QRect rect_b = option.rect.adjusted(option.rect.width() - width_b - padding, padding, -padding, -padding);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    QPainterPath path_w;
    path_w.addRoundedRect(rect_w, radius, radius);
    painter->fillPath(path_w, QColor(255, 255, 255));

    QPainterPath path_b;
    path_b.addRoundedRect(rect_b, radius, radius);
    painter->fillPath(path_b, QColor(0, 0, 0));

    QPainterPath path_d;
    path_d.addRect(rect_d);
    painter->fillPath(path_d, QColor(150, 150, 150));

    painter->setPen(Qt::black);
    painter->drawText(rect_w, Qt::AlignCenter, QString::number(white_wr * 100, 'g', 4) + "%");
    painter->setPen(Qt::white);
    if (draw_rate > 0.03) {
        painter->drawText(rect_d, Qt::AlignCenter || Qt:: , QString::number(draw_rate * 100, 'g', 4) + "%");
    }
    painter->drawText(rect_b, Qt::AlignCenter, QString::number(black_wr * 100, 'g', 4) + "%");

    painter->restore();

    QStyledItemDelegate::paint(painter, option, index);
}

QSize WinrateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(option, index);
}


