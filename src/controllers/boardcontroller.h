//
// Created by Lecka on 07/03/2025.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <qboxlayout.h>
#include <QObject>
#include <QPushButton>
#include <qtmetamacros.h>

#include "models/chessboard/boardtblmodel.h"
#include "models/chessboard/boardtblproxymodel.h"
#include "views/arrowoverlay.h"
#include "views/boardtblview.h"


class BoardController : public QObject {
    Q_OBJECT

public:
    explicit BoardController(QWidget *parent = nullptr);

    [[nodiscard]] QWidget *view() const;

    [[nodiscard]] QString get_current_fen() const;


public slots:
    void makeUciMove(const QString &uci);

signals:
    void boardChanged(const QString &fen);

private slots:
    void handleSquareClicked(const QModelIndex &proxy_index);

    void flipBoard();

    void undoMove();

private:
    void initUI();

    void initConnections();

    QFrame *m_container;
    QVBoxLayout m_layout;
    QPushButton m_flip_btn;
    QPushButton m_undo_btn;
    BoardTblView m_boardTblView;
    BoardTblModel m_boardTblModel;
    BoardTblProxyModel m_boardProxyModel;
    ArrowOverlay m_arrow_overlay;
};


#endif //BOARDCONTROLLER_H
