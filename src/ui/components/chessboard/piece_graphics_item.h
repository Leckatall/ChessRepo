//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_PIECE_GRAPHICS_ITEM_H
#define CHESSREPO_PIECE_GRAPHICS_ITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QtSvg/QSvgRenderer>

namespace View::Features::Board {
    class PieceGraphicsItem : public QGraphicsItem {
    public:
        explicit PieceGraphicsItem(const QSharedPointer<QSvgRenderer> &renderer, int size,
                                   QGraphicsItem *parent = nullptr);

        QRectF boundingRect() const override;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
            m_renderer->render(painter);
        }

        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        void dragged_to(QPointF origin, QPointF target);

    private:
        QSharedPointer<QSvgRenderer> m_renderer;
        QPointF m_origin;
        int m_square_size;
    };
}


#endif //CHESSREPO_PIECE_GRAPHICS_ITEM_H
