//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_BOARD_GRAPHICS_SCENE_H
#define CHESSREPO_BOARD_GRAPHICS_SCENE_H
#include <qevent.h>
#include <QGraphicsScene>
#include <QHash>
#include <QMap>
#include <QtSvg/QSvgRenderer>
#include <QSharedPointer>

#include "domain/chess/primitives.h"


namespace Views::Features::Board {
    class SquareGraphicsObject;
    class PieceGraphicsItem;

    class BoardGraphicsScene : public QGraphicsScene {
        Q_OBJECT

    public:
        enum class PieceType {
            None,
            WhitePawn,
            WhiteKnight,
            WhiteBishop,
            WhiteRook,
            WhiteQueen,
            WhiteKing,
            BlackPawn,
            BlackKnight,
            BlackBishop,
            BlackRook,
            BlackQueen,
            BlackKing
        };

        struct PieceData {
            PieceType type;
            Domain::Types::Chess::Square square;
        };

        explicit BoardGraphicsScene(QObject *parent = nullptr);

        void update_board(const QList<PieceData> &pieces);

    public slots:
        // void on_square_clicked(Domain::Types::Chess::Square square);

        void on_piece_dragged(const QPointF &origin, const QPointF &target);

        void onResizeEvent(QResizeEvent *event) { m_square_size = std::min(width() / 8, height() / 8); }

    signals:
        void requestMove(const Domain::Types::Chess::Move &move);

        void squareClicked(const Domain::Types::Chess::Square &square);

    private:
        void init_board();

        void cache_piece(PieceType type, const QString &file_name);

        Domain::Types::Chess::Square point_to_square(QPointF point) const;

        // Internally generated members
        const QString m_svg_path = "../../../resources/chess/";

        QHash<PieceType, QSharedPointer<QSvgRenderer> > m_piece_svg_cache;
        int m_square_size;
        QMap<Domain::Types::Chess::Square, SquareGraphicsObject *> m_squares;

        // Inputs
        QList<PieceData> m_pieces_data;
        Domain::Types::Chess::Square m_selected_square{};
    };
}


#endif //CHESSREPO_BOARD_GRAPHICS_SCENE_H
