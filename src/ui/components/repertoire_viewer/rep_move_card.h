#ifndef REPERTOIRE_VIEWER_REP_MOVE_CARD_H
#define REPERTOIRE_VIEWER_REP_MOVE_CARD_H


#include "card_widget.h"
#include "move.h"

namespace repertoire_viewer {

class MoveCard : public common::CardWidget {
  Q_OBJECT
  public:
    explicit MoveCard(Models::Move move, QWidget * parent = nullptr);


  private:
    Models::Move m_move;

};

} // namespace repertoire_viewer
#endif
