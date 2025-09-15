#ifndef _MOVE_CARD_H
#define _MOVE_CARD_H


#include "move.h"

class StatsWidget;

typedef QFrame typedef39;
class MoveCard : public typedef39 {
  Q_OBJECT
  public:
    explicit MoveCard(Models::MoveData move_data, bool recommended, QWidget * parent = nullptr);

  signals:    void clicked();


  private:
    void initLayout();

    inline void mousePressEvent(QMouseEvent * event) override {
            if (event->button() == Qt::LeftButton)
                emit clicked();
        };

    Models::MoveData m_move_data;

    bool m_recommended;

    QLabel * m_move_lbl;

    StatsWidget * m_move_stats;

};
#endif
