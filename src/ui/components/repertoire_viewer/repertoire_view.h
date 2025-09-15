#ifndef REPERTOIRE_VIEWER_REPERTOIRE_VIEW_H
#define REPERTOIRE_VIEWER_REPERTOIRE_VIEW_H


namespace Models { struct Move; } 
namespace common { class WidgetList; } 

namespace repertoire_viewer {

typedef QWidget typedef50;
class View : public typedef50 {
  Q_OBJECT
  public:
    explicit View(QWidget * parent = nullptr);

    void updateMovesWidget(const QList<Models::Move> & moves);

  signals:    void move_clicked(Models::Move _t1);


  private:
    common::WidgetList * m_moves_widget;

};

} // namespace repertoire_viewer
#endif
