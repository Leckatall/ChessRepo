//
// Created by Lecka on 15/06/2025.
//

#ifndef DECK_WIDGET_H
#define DECK_WIDGET_H
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>


class QVBoxLayout;

namespace common {
    class WidgetList : public QScrollArea {
    public:
        explicit WidgetList(QWidget *parent);

        void add_widget(QWidget *widget) const;

        void clear_widgets() const;

    protected:
        QWidget *m_container;
        QVBoxLayout *m_layout;
    };
}


#endif //DECK_WIDGET_H
