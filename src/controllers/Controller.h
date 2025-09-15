#ifndef _CONTROLLER_H
#define _CONTROLLER_H


#include "models.h"

namespace application { class Application; } 

typedef QObject typedef27;
class Controller : public typedef27 {
  Q_OBJECT
  public:
    explicit Controller(application::Application * app);

    virtual QWidget * view() const = 0;

  signals:    void routeToPage(application::Page _t1);

  public slots:    virtual void updateData() = 0;

    virtual void updateView() = 0;

};
#endif
