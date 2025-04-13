//
// Created by Lecka on 11/03/2025.
//

#ifndef WINRATEDELEGATE_H
#define WINRATEDELEGATE_H
#include <QStyledItemDelegate>

#include "models/datatypes.h"


class WinrateDelegate : public QStyledItemDelegate {
public:
    explicit WinrateDelegate(QObject *parent = nullptr): QStyledItemDelegate(parent) {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    static constexpr int PADDING = 5;
    static constexpr int CORNER_RADIUS = 5;
    static constexpr double MIN_DRAW_RATE_DISPLAY = 0.03;

    // Helper struct for width calculations
    struct BarWidths {
        int white;
        int draw;
        int black;
    };

    [[nodiscard]] static BarWidths calculate_widths(int totalWidth, const Models::PositionData& data);

    static std::tuple<QRect, QRect, QRect> createRects(const QRect& baseRect, const BarWidths& widths);

    static void draw_segment_background(QPainter* painter, const QRect& rect, const QColor& color, bool rounded);

    static void draw_segment_text(QPainter *painter, const QRect &rect, const QString &text, const QColor &color);


};



#endif //WINRATEDELEGATE_H
