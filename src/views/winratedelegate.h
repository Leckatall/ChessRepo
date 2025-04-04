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
    static constexpr int RADIUS = 5;
    static constexpr double MIN_DRAW_RATE_DISPLAY = 0.03;

    // Helper struct for width calculations
    struct BarWidths {
        int white;
        int draw;
        int black;
    };

    [[nodiscard]] static BarWidths calculate_widths(const int totalWidth, const Models::PositionData& data) {
        int width_w = static_cast<int>(totalWidth * data.white_wr());
        int width_b = static_cast<int>(totalWidth * data.black_wr());
        int width_d = totalWidth - width_w - width_b;
        return {width_w, width_d, width_b};
    }

    [[nodiscard]] static QString format_percentage(const double value) {
        return QString::number(value * 100, 'g', 4) + "%";
    }
};



#endif //WINRATEDELEGATE_H
