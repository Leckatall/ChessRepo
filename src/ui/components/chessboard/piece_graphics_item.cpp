//
// Created by Lecka on 19/09/2025.
//

#include "piece_graphics_item.h"

namespace Views::Features::Board {
    PieceGraphicsItem::PieceGraphicsItem(const QSharedPointer<QSvgRenderer> &renderer, int size,
    QGraphicsItem *parent): QGraphicsItem(parent),
                            m_renderer(renderer),
                            m_square_size(size) {
        setZValue(2);
    }

    QRectF PieceGraphicsItem::boundingRect() const {
        return QRectF(0,0, m_square_size, m_square_size);
    }

    void PieceGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
        m_origin = event->pos();
        setZValue(3);
    }

    void PieceGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            // setPos(mapToParent(event->pos() - event->lastPos()));
            setPos(event->pos());
        }
    }

    void PieceGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
        setZValue(2);
        //emit dragged_to(m_origin, event->pos());
    }
}

