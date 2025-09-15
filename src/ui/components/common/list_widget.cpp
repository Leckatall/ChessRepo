
#include "list_widget.h"

namespace common {

WidgetList::WidgetList(QWidget * parent)
        : QScrollArea(parent),
          m_container(new QWidget()),
          m_layout(new QVBoxLayout(m_container)) {

        setWidgetResizable(true);
        setWidget(m_container);
        m_layout->setAlignment(Qt::AlignTop);
        m_layout->setSpacing(8);
}

void WidgetList::add_widget() const {

        m_layout->addWidget(widget);
}

void WidgetList::clear_widgets() const {

        while (const QLayoutItem *item = m_layout->takeAt(0)) {
            delete item->widget();
            delete item;
        }
}


} // namespace common
