//
// Created by Lecka on 08/03/2025.
//

#include "boardtblview.h"

#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>

#include "squaredelegate.h"

BoardTblView::BoardTblView(QWidget *parent) : QTableView(parent) {
    // Meta-cell styling
    this->setShowGrid(false);
    setFrameStyle(Box);
    setLineWidth(1);

    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
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

    setItemDelegate(new SquareDelegate(this));
}


void BoardTblView::mousePressEvent(QMouseEvent *event) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        emit squareClicked(index);
    }
    // QTableView::mousePressEvent(event);
}

// Paints coords
// void BoardTblView::paintEvent(QPaintEvent *event) {
//     QTableView::paintEvent(event);
// }

void BoardTblView::resizeEvent(QResizeEvent *event) {
    QTableView::resizeEvent(event);

    // height, width = min(height, width)
    if (width() > height()) {
        setFixedWidth(height());
    } else {
        setFixedHeight(width());
    }

    int squareSize = width() / 8;

    for (int i = 0; i < 8; ++i) {
        setColumnWidth(i, squareSize);
        setRowHeight(i, squareSize);
    }
}


