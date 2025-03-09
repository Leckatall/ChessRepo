//
// Created by Lecka on 09/03/2025.
//

#ifndef EXPLORERTBLVIEW_H
#define EXPLORERTBLVIEW_H
#include <QTableView>
#include <qtmetamacros.h>


class ExplorerTblView : public QTableView {
    Q_OBJECT
public:
    explicit ExplorerTblView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override {}

    void mouseReleaseEvent(QMouseEvent *event) override {}

    // void paintEvent(QPaintEvent *event) override;

    signals:
        void moveClicked(QModelIndex index);

};



#endif //EXPLORERTBLVIEW_H
