//
// Created by Lecka on 19/09/2025.
//

#include "piece_graphics_item.h"

namespace View::Features::Board {
    PieceGraphicsItem::PieceGraphicsItem(const QSharedPointer<QSvgRenderer> &renderer,
                                         QGraphicsItem *parent)
        : QGraphicsItem(parent),
          m_renderer(renderer) {
        setZValue(2);
    }

    QRectF PieceGraphicsItem::boundingRect() const {
        return parentItem()->boundingRect();
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
