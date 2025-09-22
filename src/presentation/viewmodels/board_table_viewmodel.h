//
// Created by Lecka on 22/09/2025.
//

#ifndef CHESSREPO_BOARD_TABLE_VIEWMODEL_H
#define CHESSREPO_BOARD_TABLE_VIEWMODEL_H
#include <QObject>

#include "chess/board.h"
#include "models/chessboard/board_proxytblmodel.h"
#include "models/chessboard/board_tblmodel.h"

namespace Presentation::Features::Board {
    // TODO: Make this more than a shitty copy of the board_controller
    class BoardTableViewModel: public QObject {
        Q_OBJECT

    public:
        explicit BoardTableViewModel(Domain::Features::Chess::Board &board, QObject *parent = nullptr);

        [[nodiscard]] QString get_current_fen() const;

        chessboard::ProxyTblModel *boardProxyModel() { return &m_boardProxyModel; }

    public slots:
        void makeUciMove(const Domain::Types::UCIMove &uci);

        void handleSquareClicked(const QModelIndex &proxy_index);

        void updateMoveHistory();

        void flipBoard();

        void undoMove();

        signals:
            void boardChanged(const Domain::Types::FEN &fen);

        void boardHistoryChanged(const QString &pgn);

    private:
        void initConnections();

        Domain::Features::Chess::Board &m_board;
        //TODO: WHY IS ALL THE BOARD LOGIC IN THIS STUPID TABLE MODEL
        chessboard::TblModel m_boardTblModel;
        chessboard::ProxyTblModel m_boardProxyModel;
    };
}



#endif //CHESSREPO_BOARD_TABLE_VIEWMODEL_H
