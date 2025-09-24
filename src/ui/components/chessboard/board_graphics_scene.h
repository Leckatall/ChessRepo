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

#include "chess/piece.h"
#include "domain/chess/primitives.h"


namespace View::Features::Board {
    class SquareGraphicsObject;
    class PieceGraphicsItem;

    class BoardGraphicsScene : public QGraphicsScene {
        Q_OBJECT

    public:


        explicit BoardGraphicsScene(QObject *parent = nullptr);

        void updateBoard(const QList<Domain::Types::Chess::PieceData> &pieces);
        void setSelectedSquare(Domain::Types::Chess::Square *square);

        Domain::Types::Chess::Square* selectedSquare() const {return m_selected_square;}

    public slots:
        // void on_square_clicked(Domain::Types::Chess::Square square);

        void onPieceDragged(const QPointF &origin, const QPointF &target);

        void setSquareSize(int size);

        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        void requestMove(const Domain::Types::Chess::Move &move);

        void squareClicked(const Domain::Types::Chess::Square &square);

    private:
        void initBoard();

        void cachePiece(Domain::Types::Chess::PieceType type, const QString &file_name);

        // Domain::Types::Chess::Square point_to_square(QPointF point) const;

        // Internally generated members
        const QString m_svg_path = ":/chess/";

        QHash<Domain::Types::Chess::PieceType, QSharedPointer<QSvgRenderer> > m_piece_svg_cache;
        int m_square_size;
        QMap<Domain::Types::Chess::Square, SquareGraphicsObject *> m_squares;

        // Inputs
        QList<Domain::Types::Chess::PieceData> m_pieces_data;
        Domain::Types::Chess::Square* m_selected_square = nullptr;
    };
}


#endif //CHESSREPO_BOARD_GRAPHICS_SCENE_H
