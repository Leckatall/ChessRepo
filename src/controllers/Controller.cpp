
#include "Controller.h"
#include "application.h"

Controller::Controller(application::Application * app) : QObject(app) {

}

// SIGNAL 0

void Controller::routeToPage(application::Page _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

