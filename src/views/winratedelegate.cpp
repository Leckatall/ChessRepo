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

    if (pos_data.games == 0) {
        painter->drawText(option.rect, Qt::AlignCenter, "No games");
        return;
    }

    auto [rect_w, rect_d, rect_b] = createRects(option.rect, calculate_widths(option.rect.width(), pos_data));
    // painter->setRenderHint(QPainter::Antialiasing);
    draw_segment_background(painter, rect_w, Qt::white, true);
    draw_segment_background(painter, rect_b, Qt::black, true);
    draw_segment_background(painter, rect_d, QColor(150, 150, 150), false);

    draw_segment_text(painter, rect_w, Models::formatPercentage(pos_data.white_wr()), Qt::black);
    draw_segment_text(painter, rect_d, Models::formatPercentage(pos_data.draw_rate()), Qt::white);
    draw_segment_text(painter, rect_b, Models::formatPercentage(pos_data.black_wr()), Qt::white);
    painter->restore();
}

QSize WinrateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(option, index);
}

WinrateDelegate::BarWidths WinrateDelegate::calculate_widths(const int totalWidth, const Models::PositionData &data) {
    const int width_w = static_cast<int>(totalWidth * data.white_wr());
    const int width_b = static_cast<int>(totalWidth * data.black_wr());
    const int width_d = totalWidth - width_w - width_b;
    return {width_w, width_d, width_b};
}

std::tuple<QRect, QRect, QRect> WinrateDelegate::createRects(const QRect &baseRect, const BarWidths &widths) {
    QRect rect_w = baseRect.adjusted(PADDING, PADDING,
                                     -baseRect.width() + widths.white + PADDING, -PADDING);
    QRect rect_d = baseRect.adjusted(widths.white, PADDING,
                                     -baseRect.width() + widths.white + widths.draw, -PADDING);
    QRect rect_b = baseRect.adjusted(baseRect.width() - widths.black - PADDING, PADDING,
                                     -PADDING, -PADDING);
    return {rect_w, rect_d, rect_b};
}


void WinrateDelegate::draw_segment_background(QPainter *painter, const QRect &rect, const QColor &color,
                                              const bool rounded) {
    painter->setPen(Qt::NoPen);
    QPainterPath path;
    if (rounded) {
        path.addRoundedRect(rect, CORNER_RADIUS, CORNER_RADIUS);
    } else {
        path.addRect(rect);
    }
    painter->fillPath(path, color);
}

void WinrateDelegate::draw_segment_text(QPainter* painter, const QRect& rect, const QString& text, const QColor& color) {
    painter->setPen(color);
    // Ensure text fits in rectangle
    const QFontMetrics fm(painter->font());
    const QString elidedText = fm.elidedText(text, Qt::ElideRight, rect.width());
    painter->drawText(rect, Qt::AlignCenter, elidedText);
}

