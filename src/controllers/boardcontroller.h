//
// Created by Lecka on 07/03/2025.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <qboxlayout.h>
#include <QObject>
#include <qtmetamacros.h>

#include "models/chessboard/boardtblmodel.h"
#include "models/chessboard/boardtblproxymodel.h"
#include "views/boardtblview.h"


class BoardController : public QObject {
    Q_OBJECT

public:
    explicit BoardController(QWidget *parent = nullptr);

    [[nodiscard]] QWidget *view() const;

    [[nodiscard]] QString get_current_fen() const;

signals:
    void boardChanged(const QString &fen);

private slots:
    void handleSquareClicked(const QModelIndex &index);

private:
    void initUI();
    void initConnections();
    QFrame *m_container;
    QVBoxLayout m_layout;
    BoardTblView m_boardTblView;
    BoardTblModel m_boardTblModel;
    BoardTblProxyModel m_boardProxyModel;

};


#endif //BOARDCONTROLLER_H
