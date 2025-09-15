#ifndef REPERTOIRE_VIEWER_REPERTOIRE_VIEWER_CONTROLLER_H
#define REPERTOIRE_VIEWER_REPERTOIRE_VIEWER_CONTROLLER_H


class RepertoireService;
namespace repertoire_viewer { class View; } 
namespace Models { class FEN; } 
namespace Models { class UCIMove; } 

namespace repertoire_viewer {

typedef QObject typedef29;
class Controller : public typedef29 {
  Q_OBJECT
  public:
    explicit Controller(::RepertoireService & service, QObject * parent = nullptr);

    inline View * view() const { return m_view; };

  public slots:    void getUciMovesForFEN(const Models::FEN & fen);

    void showMoves(const QList<Models::Move> & moves) const;

  signals:    void moveClicked(Models::UCIMove _t1);

    void requestMoveModels(QList<Models::UCIMove> _t1);


  private:
    void initConnections();

    ::RepertoireService & m_rep_service;

    View * m_view;

};

} // namespace repertoire_viewer
#endif
