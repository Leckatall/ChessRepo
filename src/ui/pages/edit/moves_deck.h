#ifndef _MOVES_DECK_H
#define _MOVES_DECK_H


class MoveCard;

typedef QFrame typedef53;
class MovesDeck : public typedef53 {
  Q_OBJECT
  public:
    explicit MovesDeck(QWidget * parent = nullptr);

    void updateMoveCards(QList<MoveCard*> move_cards);


  private:
    QScrollArea * m_scrollArea;

    QWidget * m_scroll_widget;

    QVBoxLayout * m_scroll_layout;

};
#endif
