//
// Created by Lecka on 13/06/2025.
//

#include "stats_painter.h"

#include <QPainterPath>

#include "presentation/utils.h"
#include "presentation/viewmodels/explorer_viewmodel.h"

void StatsPainter::paint(QPainter *painter, QRect rect, const Domain::Types::PositionStats &stats) {
    if (stats.games == 0) {
        painter->drawText(rect, Qt::AlignCenter, "No games");
        return;
    }

    auto [rect_w, rect_d, rect_b] = createRects(rect, calculate_widths(rect.width(), stats));
    // painter->setRenderHint(QPainter::Antialiasing);
    draw_segment_background(painter, rect_w, QColor(255, 255, 255), true);
    draw_segment_background(painter, rect_b, QColor(0, 0, 0), true);
    draw_segment_background(painter, rect_d, QColor(150, 150, 150), false);

    draw_segment_text(painter, rect_w, Presentation::Utils::formatPercentage(stats.white_wr()), Qt::black);
    draw_segment_text(painter, rect_d, Presentation::Utils::formatPercentage(stats.draw_rate()), Qt::white);
    draw_segment_text(painter, rect_b, Presentation::Utils::formatPercentage(stats.black_wr()), Qt::white);
}

StatsPainter::BarWidths StatsPainter::calculate_widths(int totalWidth, const Domain::Types::PositionStats &data) {
    const int width_w = static_cast<int>(totalWidth * data.white_wr());
    const int width_b = static_cast<int>(totalWidth * data.black_wr());
    const int width_d = totalWidth - width_w - width_b;
    return {width_w, width_d, width_b};
}

std::tuple<QRect, QRect, QRect> StatsPainter::createRects(const QRect &baseRect, const BarWidths &widths) {
    QRect rect_w = baseRect.adjusted(PADDING, PADDING,
                                     -baseRect.width() + widths.white + PADDING, -PADDING);
    QRect rect_d = baseRect.adjusted(widths.white, PADDING,
                                     -baseRect.width() + widths.white + widths.draw, -PADDING);
    QRect rect_b = baseRect.adjusted(baseRect.width() - widths.black - PADDING, PADDING,
                                     -PADDING, -PADDING);
    return {rect_w, rect_d, rect_b};
}

void StatsPainter::draw_segment_background(QPainter *painter, const QRect &rect, const QColor &color, bool rounded) {
    painter->setPen(Qt::NoPen);
    QPainterPath path;
    if (rounded) {
        path.addRoundedRect(rect, CORNER_RADIUS, CORNER_RADIUS);
    } else {
        path.addRect(rect);
    }
    painter->fillPath(path, color);
}

void StatsPainter::draw_segment_text(QPainter *painter, const QRect &rect, const QString &text, const QColor &color) {
    painter->setPen(color);
    // Ensure text fits in rectangle
    const QFontMetrics fm(painter->font());
    const QString elidedText = fm.elidedText(text, Qt::ElideRight, rect.width());
    painter->drawText(rect, Qt::AlignCenter, elidedText);
}
