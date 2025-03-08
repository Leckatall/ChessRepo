//
// Created by Lecka on 07/03/2025.
//

#include "squaredelegate.h"

#include <QPainter>

#include "models/boardtblmodel.h"



void SquareDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    const QRect rect = option.rect;
    const auto data = index.data().value<SquareData>();

    if(data.isLight) {
        painter->fillRect(rect, QColor(100, 100, 100, 100));
    } else {
        painter->fillRect(rect, QColor(0, 0, 0, 100));
    }

    if (data.isSelected) {
        painter->fillRect(rect, QColor(124, 192, 203, 180));
    }

    // Draw highlight
    if (data.isHighlighted) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(173, 216, 230, 128));
        painter->drawEllipse(rect.center(), rect.width() / 4, rect.height() / 4);
    }

    // Draw piece
    const QString unicode_piece = STR_TO_UNICODE_PIECE[data.piece];
    painter->setPen(Qt::white);
    painter->setFont(QFont(piece_font, 24));
    painter->drawText(rect, Qt::AlignCenter, unicode_piece);
}
