
#include "winrate_delegate.h"
#include "position.h"

void WinrateDelegate::paint() const {

    painter->save();
    const auto pos_data = index.data(Qt::UserRole).value<Models::PositionStats>();

    if (pos_data.games == 0) {
        painter->drawText(option.rect, Qt::AlignCenter, "No games");
        return;
    }

    auto [rect_w, rect_d, rect_b] = createRects(option.rect, calculate_widths(option.rect.width(), pos_data));
    // painter->setRenderHint(QPainter::Antialiasing);
    draw_segment_background(painter, rect_w, Qt::white, true);
    draw_segment_background(painter, rect_b, Qt::black, true);
    draw_segment_background(painter, rect_d, QColor(150, 150, 150), false);

    draw_segment_text(painter, rect_w, Utils::formatPercentage(pos_data.white_wr()), Qt::black);
    draw_segment_text(painter, rect_d, Utils::formatPercentage(pos_data.draw_rate()), Qt::white);
    draw_segment_text(painter, rect_b, Utils::formatPercentage(pos_data.black_wr()), Qt::white);
    painter->restore();
}

QSize WinrateDelegate::sizeHint() const {

    return QStyledItemDelegate::sizeHint(option, index);
}

constexpr int WinrateDelegate::PADDING;

constexpr int WinrateDelegate::CORNER_RADIUS;

constexpr double WinrateDelegate::MIN_DRAW_RATE_DISPLAY;

std::tuple<QRect, QRect, QRect> WinrateDelegate::createRects()
{

    QRect rect_w = baseRect.adjusted(PADDING, PADDING,
                                     -baseRect.width() + widths.white + PADDING, -PADDING);
    QRect rect_d = baseRect.adjusted(widths.white, PADDING,
                                     -baseRect.width() + widths.white + widths.draw, -PADDING);
    QRect rect_b = baseRect.adjusted(baseRect.width() - widths.black - PADDING, PADDING,
                                     -PADDING, -PADDING);
    return {rect_w, rect_d, rect_b};
}

void WinrateDelegate::draw_segment_text()
{

    painter->setPen(color);
    // Ensure text fits in rectangle
    const QFontMetrics fm(painter->font());
    const QString elidedText = fm.elidedText(text, Qt::ElideRight, rect.width());
    painter->drawText(rect, Qt::AlignCenter, elidedText);
}

