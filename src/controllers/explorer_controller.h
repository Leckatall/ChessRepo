#ifndef EXPLORER_EXPLORER_CONTROLLER_H
#define EXPLORER_EXPLORER_CONTROLLER_H


#include "explorer_tblmodel.h"

class LichessService;
namespace explorer { class View; } 
namespace Models { class FEN; } 
namespace Models { class UCIMove; } 

namespace explorer {

typedef QObject typedef28;
class Controller : public typedef28 {
  Q_OBJECT
  public:
    // TODO: Add engine support
    // TODO: Add integration with openerController and highlight prepped moves
    explicit Controller(::LichessService & service, QObject * parent = nullptr);

    inline View * view() const { return m_view; };

  public slots:    void exploreFen(const Models::FEN & fen) const;

    void updateMoves(const QList<Models::MoveData> & moves);

    void updatePositionData(const Models::PositionData & position);

  signals:    void moveClicked(Models::UCIMove _t1);


  private:
    void initConnections();

    ::LichessService & m_lichess_api;

    Models::PositionData m_current_position {};

    TblModel m_explorerTblModel;

    View * m_view;

};

} // namespace explorer
#endif
