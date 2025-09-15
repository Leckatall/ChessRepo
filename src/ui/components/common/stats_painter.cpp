
#include "stats_painter.h"

void StatsPainter::paint()
{

    if (stats.games == 0) {
        painter->drawText(rect, Qt::AlignCenter, "No games");
        return;
    }

    auto [rect_w, rect_d, rect_b] = createRects(rect, calculate_widths(rect.width(), stats));
    // painter->setRenderHint(QPainter::Antialiasing);
    draw_segment_background(painter, rect_w, Qt::white, true);
    draw_segment_background(painter, rect_b, Qt::black, true);
    draw_segment_background(painter, rect_d, QColor(150, 150, 150), false);

    draw_segment_text(painter, rect_w, Models::formatPercentage(stats.white_wr()), Qt::black);
    draw_segment_text(painter, rect_d, Models::formatPercentage(stats.draw_rate()), Qt::white);
    draw_segment_text(painter, rect_b, Models::formatPercentage(stats.black_wr()), Qt::white);
}

constexpr int StatsPainter::PADDING;

constexpr int StatsPainter::CORNER_RADIUS;

constexpr double StatsPainter::MIN_DRAW_RATE_DISPLAY;

StatsPainter::BarWidths StatsPainter::calculate_widths()
{

    const int width_w = static_cast<int>(totalWidth * data.white_wr());
    const int width_b = static_cast<int>(totalWidth * data.black_wr());
    const int width_d = totalWidth - width_w - width_b;
    return {width_w, width_d, width_b};
}

std::tuple<QRect, QRect, QRect> StatsPainter::createRects()
{

    QRect rect_w = baseRect.adjusted(PADDING, PADDING,
                                     -baseRect.width() + widths.white + PADDING, -PADDING);
    QRect rect_d = baseRect.adjusted(widths.white, PADDING,
                                     -baseRect.width() + widths.white + widths.draw, -PADDING);
    QRect rect_b = baseRect.adjusted(baseRect.width() - widths.black - PADDING, PADDING,
                                     -PADDING, -PADDING);
    return {rect_w, rect_d, rect_b};
}

void StatsPainter::draw_segment_background()
{

    painter->setPen(Qt::NoPen);
    QPainterPath path;
    if (rounded) {
        path.addRoundedRect(rect, CORNER_RADIUS, CORNER_RADIUS);
    } else {
        path.addRect(rect);
    }
    painter->fillPath(path, color);
}

void StatsPainter::draw_segment_text()
{

    painter->setPen(color);
    // Ensure text fits in rectangle
    const QFontMetrics fm(painter->font());
    const QString elidedText = fm.elidedText(text, Qt::ElideRight, rect.width());
    painter->drawText(rect, Qt::AlignCenter, elidedText);
}

