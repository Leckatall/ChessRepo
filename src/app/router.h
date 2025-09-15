#ifndef APPLICATION_ROUTER_H
#define APPLICATION_ROUTER_H


#include "models.h"

namespace application {

typedef QStackedWidget typedef25;
class Router : public typedef25 {
  Q_OBJECT
  public:
    explicit Router(QWidget * parent = nullptr);

    void navigateTo(Page page);

    void addView(Page page, QWidget * view);

  signals:    void pageChanged(Page _t1);


  private:
    QMap<Page,QWidget*> m_pages;

};

} // namespace application
#endif
