//
// Created by Lecka on 09/03/2025.
//

#include "explorer_tblview.h"

#include <QHeaderView>
#include <QMouseEvent>

#include "winrate_delegate.h"

namespace explorer {
    TblView::TblView(QWidget *parent) : QTableView(parent) {

    }

    void TblView::initUI() {
        this->setShowGrid(false);
        setFrameStyle(Box);
        setLineWidth(1);

        this->verticalHeader()->setVisible(false);
        this->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        this->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->setSelectionMode(SingleSelection);
        setSelectionBehavior(SelectRows);

        // Drag and drop settings
        // setDragEnabled(true);
        // setAcceptDrops(true);
        // setDropIndicatorShown(true);
        // setDragDropMode(InternalMove);

        // setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        setEditTriggers(NoEditTriggers);
        setItemDelegateForColumn(2, new WinrateDelegate(this));
    }
}


