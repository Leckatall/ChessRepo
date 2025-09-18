//
// Created by Lecka on 13/06/2025.
//

#ifndef STATS_PAINTER_H
#define STATS_PAINTER_H
#include <QPainter>
#include <QWidget>
#include <utility>

#include "models/datatypes.h"
#include "presentation/models/explorer_tblmodel.h"


class StatsPainter {
public:
    static void paint(QPainter *painter, QRect rect, const Domain::Types::PositionStats &stats);

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

    [[nodiscard]] static BarWidths calculate_widths(int totalWidth, const Domain::Types::PositionStats& data);

    static std::tuple<QRect, QRect, QRect> createRects(const QRect& baseRect, const BarWidths& widths);

    static void draw_segment_background(QPainter* painter, const QRect& rect, const QColor& color, bool rounded);

    static void draw_segment_text(QPainter *painter, const QRect &rect, const QString &text, const QColor &color);
};

class StatsWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatsWidget(Domain::Types::PositionStats stats, QWidget *parent = nullptr)
        : QWidget(parent),
          m_stats(std::move(stats)) {
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        StatsPainter::paint(&painter, rect(), m_stats);
    }

private:
    Domain::Types::PositionStats m_stats;
};


#endif //STATS_PAINTER_H
