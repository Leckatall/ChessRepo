//
// Created by Lecka on 13/06/2025.
//

#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include "../presentation/models/chessboard/board_proxytblmodel.h"
#include "../presentation/models/chessboard/board_tblmodel.h"
#include "ui/components/chessboard/board_view.h"


namespace application {
    class Application;
}

namespace chessboard {
    class Controller : public QObject {
        Q_OBJECT

    public:
        explicit Controller(QObject *parent);

        [[nodiscard]] View *view() const { return m_view; }

        [[nodiscard]] QString get_current_fen() const;

    public slots:
        void makeUciMove(const QString &uci);

    signals:
        void boardChanged(const QString &fen);

    private slots:
        void handleSquareClicked(const QModelIndex &proxy_index);

        void updateMoveHistory();

        void flipBoard();

        void undoMove();

    private:
        void initConnections();

        TblModel m_boardTblModel;
        ProxyTblModel m_boardProxyModel;
        View *m_view;
    };
}


#endif //BOARD_CONTROLLER_H
