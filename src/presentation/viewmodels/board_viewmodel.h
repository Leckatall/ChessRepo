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

        Q_PROPERTY(View::Features::Board::BoardGraphicsScene* scene READ scene CONSTANT)

    public:
        explicit BoardViewModel(Domain::Features::Chess::Board &board, QObject *parent = nullptr);

        [[nodiscard]] Domain::Types::FEN getFen() const {
            return m_board.fen();
        }

        [[nodiscard]] View::Features::Board::BoardGraphicsScene* scene() { return &m_scene; }

        // QPointF squareToPoint(const Domain::Types::Chess::Square &square) const;
        // QRectF squareToRect(const Domain::Types::Chess::Square &square) const;
        //
        // Domain::Types::Chess::Square pointToSquare(const QPointF &point) const;

        // DEPRECATED
        // [[nodiscard]] Domain::Types::Chess::Square getSelection() const {
        //     qDebug() << "Why call BoardViewModel::getSelection()?";
        //     return m_selected_square;
        // }

    public slots:
        void updateScene();
        // void makeMove(const Domain::Types::Chess::Move &move);

        void onSquareClicked(const Domain::Types::Chess::Square &square);

        // void sceneResized() {m_square_size = std::ranges::min(m_scene.width() / 8, m_scene.height() / 8);}

        void flipBoard();

        void undoMove();

    signals:
        void currentFenChanged(Domain::Types::FEN fen);

    private:
        void initConnections();
        Domain::Features::Chess::Board &m_board;

        View::Features::Board::BoardGraphicsScene m_scene;
        bool m_white_on_bottom = true;
    };
}


#endif //CHESSREPO_BOARD_VIEWMODEL_H
