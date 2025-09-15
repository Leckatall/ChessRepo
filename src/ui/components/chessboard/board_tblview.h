//
// Created by Lecka on 08/03/2025.
//

#ifndef BOARDTBLVIEW_H
#define BOARDTBLVIEW_H
#include <QTableView>

#include "models/chessboard/board_tblmodel.h"

namespace chessboard {
    class TblView : public QTableView {
        Q_OBJECT

    public:
        explicit TblView(QWidget *parent = nullptr);

        signals:
            void geometryChanged();

    protected:
        void mousePressEvent(QMouseEvent *event) override;

        void mouseDoubleClickEvent(QMouseEvent *event) override {
        }

        void mouseReleaseEvent(QMouseEvent *event) override {
        }

        // void paintEvent(QPaintEvent *event) override;

        void resizeEvent(QResizeEvent *event) override;

        signals:
            void squareClicked(QModelIndex index);
    };
}



#endif //BOARDTBLVIEW_H
