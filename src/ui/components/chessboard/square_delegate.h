#ifndef CHESSBOARD_SQUARE_DELEGATE_H
#define CHESSBOARD_SQUARE_DELEGATE_H


namespace chessboard {

typedef QStyledItemDelegate typedef43;
class SquareDelegate : public typedef43 {
  public:
    inline explicit SquareDelegate(QObject * parent = nullptr) : QStyledItemDelegate(parent) {
            };

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;


  private:
    QString piece_font=  "Consolas";

    QColor light_square_color=  QColor(100, 100, 100, 100);

    QColor dark_square_color=  QColor(0, 0, 0, 100);

};

} // namespace chessboard
#endif
