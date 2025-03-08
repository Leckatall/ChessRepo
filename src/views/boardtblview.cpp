//
// Created by Lecka on 08/03/2025.
//

#include "boardtblview.h"

#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>

#include "squaredelegate.h"

BoardTblView::BoardTblView(QWidget *parent) : QTableView(parent), m_coordinateFont(QFont("Arial", 8)) {
    // Meta-cell styling
    this->setShowGrid(false);
    setFrameStyle(Box);
    setLineWidth(1);

    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    // this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

void BoardTblView::setBoard(BoardTblModel *model) {
    setModel(model);

    setItemDelegate(new SquareDelegate);
}


void BoardTblView::mousePressEvent(QMouseEvent *event) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        emit squareClicked(index);
    }
    // QTableView::mousePressEvent(event);
}

// Paints coords
void BoardTblView::paintEvent(QPaintEvent *event) {
    // First let the table view do its normal painting
    QTableView::paintEvent(event);

    QPainter painter(viewport());
    painter.setFont(m_coordinateFont);

    // Draw file coordinates (a-h)
    for (int col = 0; col < 8; col++) {
        QRect rect = visualRect(model()->index(7, col));
        painter.drawText(
            QRect(rect.right() - 20, rect.bottom() - 20, 15, 15),
            Qt::AlignCenter,
            QString(QChar('a' + col))
        );
    }

    // Draw rank coordinates (1-8)
    for (int row = 0; row < 8; row++) {
        QRect rect = visualRect(model()->index(row, 0));
        painter.drawText(
            QRect(rect.left() + 5, rect.top() + 5, 15, 15),
            Qt::AlignCenter,
            QString::number(8 - row)
        );
    }
}

void BoardTblView::resizeEvent(QResizeEvent *event) {
    QTableView::resizeEvent(event);
    setFixedHeight(parentWidget()->height());
    setFixedWidth(parentWidget()->width());

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


