
#include "board_tblview.h"

namespace chessboard {

TblView::TblView(QWidget * parent) : QTableView(parent) {

        // Meta-cell styling
        this->setShowGrid(true);
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

// SIGNAL 0

void TblView::geometryChanged() {

    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

void TblView::mousePressEvent() {

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

void TblView::resizeEvent(QResizeEvent * event) {

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
        emit geometryChanged();
}

// SIGNAL 1

void TblView::squareClicked(QModelIndex _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}


} // namespace chessboard
