//
// Created by Lecka on 07/03/2025.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QObject>
#include <qtmetamacros.h>

#include "models/boardtblmodel.h"
#include "models/boardtblproxymodel.h"
#include "views/boardtblview.h"


class BoardController: public QObject {
    Q_OBJECT
public:
    explicit BoardController(QObject *parent = nullptr);
    ~BoardController() override {
        delete m_boardTblView;
    }
    BoardTblView* tbl_view() const;

private slots:
    void handleSquareClicked(const QModelIndex &index) const;

private:
    BoardTblModel* m_boardTblModel;
    BoardTblProxyModel* m_boardProxyModel;
    BoardTblView* m_boardTblView;
};



#endif //BOARDCONTROLLER_H
