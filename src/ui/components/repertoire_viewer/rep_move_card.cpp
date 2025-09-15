
#include "rep_move_card.h"

namespace repertoire_viewer {

MoveCard::MoveCard(Models::Move move, QWidget * parent)
        : m_move(std::move(move)),
          CardWidget(m_move.san, parent) {

}


} // namespace repertoire_viewer
