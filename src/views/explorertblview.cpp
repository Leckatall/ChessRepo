//
// Created by Lecka on 09/03/2025.
//

#include "explorertblview.h"

#include <QHeaderView>
#include <QMouseEvent>

ExplorerTblView::ExplorerTblView(QWidget *parent) : QTableView(parent) {
    // Meta-cell styling
    this->setShowGrid(false);
    setFrameStyle(Box);
    setLineWidth(1);

    this->horizontalHeader()->setVisible(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->setSelectionMode(SingleSelection);
    setSelectionBehavior(SelectItems);

    // Drag and drop settings
    // setDragEnabled(true);
    // setAcceptDrops(true);
    // setDropIndicatorShown(true);
    // setDragDropMode(InternalMove);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setEditTriggers(NoEditTriggers);
}

void ExplorerTblView::mousePressEvent(QMouseEvent *event) {
        QModelIndex index = indexAt(event->pos());
        if (index.isValid()) {
            emit moveClicked(index);
        }

    QTableView::mousePressEvent(event);
}
