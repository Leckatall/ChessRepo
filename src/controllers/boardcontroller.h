//
// Created by Lecka on 07/03/2025.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QObject>
#include <qtmetamacros.h>

#include "models/boardtblmodel.h"
#include "views/boardtblview.h"


class BoardController: public QObject {
    Q_OBJECT
public:
    BoardController(BoardTblModel *model, BoardTblView *view, QObject *parent = nullptr);

private slots:
    void handleSquareClicked(const QModelIndex &index);

private:
    BoardTblModel *m_boardTblModel;
    BoardTblView *m_boardTblView;
    QModelIndex m_selected_square = {};
    QSet<QModelIndex> m_targeted_squares;
};



#endif //BOARDCONTROLLER_H
