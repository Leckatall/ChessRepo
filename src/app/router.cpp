
#include "router.h"

namespace application {

Router::Router(QWidget * parent): QStackedWidget(parent) {

}

// SIGNAL 0

void Router::pageChanged(Page _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}


} // namespace application
