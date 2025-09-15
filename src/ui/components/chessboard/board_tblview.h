#ifndef CHESSBOARD_BOARD_TBLVIEW_H
#define CHESSBOARD_BOARD_TBLVIEW_H


namespace chessboard {

typedef QTableView typedef41;
class TblView : public typedef41 {
  Q_OBJECT
  public:
    explicit TblView(QWidget * parent = nullptr);

  signals:    void geometryChanged();


  protected:
    void mousePressEvent(QMouseEvent * event) override;

    inline void mouseDoubleClickEvent(QMouseEvent * event) override {
            };

    inline void mouseReleaseEvent(QMouseEvent * event) override {
            };

    // void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;

  signals:    void squareClicked(QModelIndex _t1);

};

} // namespace chessboard
#endif
