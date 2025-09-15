#ifndef CHESSBOARD_BOARD_CONTROLLER_H
#define CHESSBOARD_BOARD_CONTROLLER_H


#include "explorer_tblmodel.h"
#include "board_proxytblmodel.h"

namespace chessboard { class View; } 
namespace Models { class FEN; } 

namespace chessboard {

typedef QObject typedef26;
class Controller : public typedef26 {
  Q_OBJECT
  public:
    explicit Controller(QObject * parent);

    inline View * view() const { return m_view; };

    QString get_current_fen() const;

  public slots:    void makeUciMove(const QString & uci);

    void emitModelsFromUcis(QList<Models::UCIMove> uci_moves);

  signals:    void boardChanged(const Models::FEN & _t1);

    void convertedUcis(QList<Models::Move> _t1);

  private slots:
  private:
    void handleSquareClicked(const QModelIndex & proxy_index);

    void updateMoveHistory();

    void flipBoard();

    void undoMove();

    void initConnections();

    TblModel m_boardTblModel;

    ProxyTblModel m_boardProxyModel;

    View * m_view;

};

} // namespace chessboard
#endif
