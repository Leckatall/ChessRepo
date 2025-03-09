//
// Created by Lecka on 07/03/2025.
//

#include "squaredelegate.h"

#include <QPainter>

#include "models/chessboard/boardtblmodel.h"



void SquareDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    const QRect rect = option.rect;
    const auto data = index.data().value<SquareData>();

    const auto square_color = data.isLight ? light_square_color : dark_square_color;
    painter->fillRect(rect, square_color);


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

    // Draw coords
    // MAYBE: put drawing of coords in seperate function
    const auto coords_color = data.isLight ? dark_square_color : light_square_color;
    int padding = 2;
    painter->setPen(coords_color);
    painter->setFont(QFont("Arial", 16, QFont::Weight::Bold));
    // Draw coords if appropriate
    if(index.row() == 7) {
        // Draw file headings
        auto bottom_right_rect = QRect(rect.right() - rect.width() / 4 - padding,
                                        rect.bottom() - rect.height() / 4 - padding,
                                        rect.width() / 4, rect.height() / 4);
        QString file = index.model()->headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();
        painter->drawText(bottom_right_rect, Qt::AlignCenter, file);
    }
    if(index.column() == 0) {
        // Draw rank headings
        auto top_left_rect = QRect(rect.left() + padding,
                                        rect.top() + padding,
                                        rect.width() / 4, rect.height() / 4);
        QString rank = index.model()->headerData(index.row(), Qt::Vertical, Qt::DisplayRole).toString();
        painter->drawText(top_left_rect, Qt::AlignCenter, rank);
    }
}
