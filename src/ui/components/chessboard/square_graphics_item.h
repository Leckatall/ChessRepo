//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_SQUARE_GRAPHICS_ITEM_H
#define CHESSREPO_SQUARE_GRAPHICS_ITEM_H
#include <qbrush.h>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QSvgRenderer>

#include "domain/chess/primitives.h"

namespace View::Features::Board {
    constexpr QColor LIGHT_SQUARE_COLOR(100, 100, 100, 100);
    constexpr QColor DARK_SQUARE_COLOR(0, 0, 0, 100);

    class SquareGraphicsObject : public QGraphicsRectItem {
    public:
        explicit SquareGraphicsObject(const Domain::Types::Chess::Square square, int size,
                                      QGraphicsItem *parent = nullptr)
            : QGraphicsRectItem(parent), m_square(square), m_size(size) {
            setZValue(1);
        }

        QRectF boundingRect() const override { return QRectF(0, 0, m_size, m_size); }

        void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override {
            p->setBrush({((m_square.rank() + m_square.file()) % 2 == 0) ? DARK_SQUARE_COLOR : LIGHT_SQUARE_COLOR});
            p->drawRect(boundingRect());
            p->setPen({((m_square.rank() + m_square.file()) % 2 != 0) ? DARK_SQUARE_COLOR : LIGHT_SQUARE_COLOR});
            p->drawText(boundingRect().center(),
                        QString("%1%2").arg(static_cast<char>('a' + m_square.file() - 1)).arg(m_square.rank()));
            if (m_highlighted) {
                if (m_piece_renderer) {
                    p->setBrush(QColor(0, 255, 0, 100));
                    p->drawRect(boundingRect());
                    p->setBrush({((m_square.rank() + m_square.file()) % 2 == 0) ? DARK_SQUARE_COLOR : LIGHT_SQUARE_COLOR});
                    p->drawEllipse(boundingRect());
                    m_piece_renderer->render(p, QRectF(0, 0, m_size, m_size));
                }else {
                    p->setBrush(QColor(0, 255, 0, 100));
                    p->drawEllipse(boundingRect());
                }
            }else {
                if (m_piece_renderer) {
                    m_piece_renderer->render(p, QRectF(0, 0, m_size, m_size));
                }
            }

            QGraphicsRectItem::paint(p, opt, w);
        }

        void setPiece(const QSharedPointer<QSvgRenderer> &piece_renderer) { m_piece_renderer = piece_renderer; }

        [[nodiscard]] Domain::Types::Chess::Square getSquare() const { return m_square; }
        void setHighlighted(const bool highlighted) { m_highlighted = highlighted; }
        void setTargeted(const bool targeted) { m_targeted = targeted; }
        void setSize(const int size) { m_size = size; }

        [[nodiscard]] int size() const { return m_size; }

    private:
        Domain::Types::Chess::Square m_square;
        int m_size;
        QSharedPointer<QSvgRenderer> m_piece_renderer = nullptr;
        bool m_highlighted = false;
        bool m_targeted = false;
    };
}

#endif //CHESSREPO_SQUARE_GRAPHICS_ITEM_H
