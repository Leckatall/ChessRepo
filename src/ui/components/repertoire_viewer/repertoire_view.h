//
// Created by Lecka on 15/06/2025.
//

#ifndef REPERTOIRE_VIEW_H
#define REPERTOIRE_VIEW_H
#include <qtmetamacros.h>
#include <QWidget>

#include "models/datatypes.h"
#include "ui/components/common/list_widget.h"


namespace repertoire_viewer {
    class View : public QWidget {
        Q_OBJECT

    public:
        explicit View(QWidget *parent = nullptr);

        void updateMovesWidget(const QList<Models::Move>& moves);

    signals:
        void move_clicked(Models::Move move);

    private:
        common::WidgetList *m_moves_widget;
    };
}


#endif //REPERTOIRE_VIEW_H
