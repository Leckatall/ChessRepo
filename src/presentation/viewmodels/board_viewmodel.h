//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_BOARD_VIEWMODEL_H
#define CHESSREPO_BOARD_VIEWMODEL_H
#include <QObject>

#include "domain/chess/board.h"
#include "domain/types/fen.h"
#include "presentation/models/chessboard/board_proxytblmodel.h"
#include "presentation/models/chessboard/board_tblmodel.h"
#include "ui/components/chessboard/board_graphics_scene.h"

namespace Presentation::Features::Board {
    class BoardViewModel : public QObject {
        Q_OBJECT

        Q_PROPERTY(Views::Features::Board::BoardGraphicsScene* scene READ scene CONSTANT)

    public:
        explicit BoardViewModel(Domain::Features::Chess::Board &board, QObject *parent = nullptr);

        [[nodiscard]] QString getFen() const {
            qDebug() << "Why call BoardViewModel::getFen()?";
            return QString::fromStdString(m_board.fen());
        }

        [[nodiscard]] Views::Features::Board::BoardGraphicsScene *scene() { return &m_scene; }

        // DEPRECATED
        // [[nodiscard]] Domain::Types::Chess::Square getSelection() const {
        //     qDebug() << "Why call BoardViewModel::getSelection()?";
        //     return m_selected_square;
        // }

    public slots:
        void makeMove(const Domain::Types::Chess::Move &move);

        void onSquareClicked(Domain::Types::Chess::Square square);

    signals:
        void currentFenChanged(Domain::Types::FEN fen);

        void refresh();

    private slots:
        void flipBoard();

        void undoMove();

    private:
        Views::Features::Board::BoardGraphicsScene m_scene;

        Domain::Features::Chess::Board &m_board;
        bool m_white_on_bottom = true;
    };
}


#endif //CHESSREPO_BOARD_VIEWMODEL_H
