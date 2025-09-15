#ifndef _WINRATE_DELEGATE_H
#define _WINRATE_DELEGATE_H


namespace Models { struct PositionStats; } 

typedef QStyledItemDelegate typedef49;
// TODO: Use stats painter
class WinrateDelegate : public typedef49 {
  public:
    inline explicit WinrateDelegate(QObject * parent = nullptr) : QStyledItemDelegate(parent) {
        };

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;


  private:
    static constexpr int PADDING=  5;

    static constexpr int CORNER_RADIUS=  5;

    static constexpr double MIN_DRAW_RATE_DISPLAY=  0.03;


  public:
    struct BarWidths {
        int white;

        int draw;

        int black;

    };
    

  private:
    static BarWidths calculate_widths(int totalWidth, const Models::PositionStats & data);

    static std::tuple<QRect, QRect, QRect> createRects(const QRect & baseRect, const BarWidths & widths);

    static void draw_segment_background(QPainter * painter, const QRect & rect, const QColor & color, bool rounded);

    static void draw_segment_text(QPainter * painter, const QRect & rect, const QString & text, const QColor & color);

};
#endif
