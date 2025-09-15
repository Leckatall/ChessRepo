#ifndef CHESSBOARD_BOARD_VIEW_H
#define CHESSBOARD_BOARD_VIEW_H


namespace chessboard { class TblView; } 

namespace chessboard {

typedef QWidget typedef42;
class View : public typedef42 {
  Q_OBJECT
  public:
    explicit View(QWidget * parent = nullptr);

    inline void setTblModel(QAbstractItemModel * model) const {m_tblView->setModel(model);};

    void setHistoryLabel(const QString & pgn_str) const;

  signals:    void square_clicked(QModelIndex _t1);

    void flipRequested();

    void undoMoveRequested();


  private:
    void initConnections();

    QPushButton * m_flip_btn;

    QPushButton * m_undo_btn;

    QLabel * m_move_history_lbl;

    TblView * m_tblView;

};

} // namespace chessboard
#endif
