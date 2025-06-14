//
// Created by Lecka on 09/03/2025.
//

#ifndef EXPLORERTBLVIEW_H
#define EXPLORERTBLVIEW_H
#include <QTableView>
#include <qtmetamacros.h>

#include "models/datatypes.h"

namespace explorer{
    class TblView : public QTableView {
        Q_OBJECT
    public:
        explicit TblView(QWidget *parent = nullptr);

        void initUI();
        //
        // protected:
        //     void mousePressEvent(QMouseEvent *event) override;
        //
        //     void mouseDoubleClickEvent(QMouseEvent *event) override {}
        //
        //     void mouseReleaseEvent(QMouseEvent *event) override {}
        //
        //     // void paintEvent(QPaintEvent *event) override;

    };
}




#endif //EXPLORERTBLVIEW_H
