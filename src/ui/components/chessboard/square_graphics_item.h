//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_SQUARE_GRAPHICS_ITEM_H
#define CHESSREPO_SQUARE_GRAPHICS_ITEM_H
#include <qbrush.h>
#include <QGraphicsRectItem>
#include <QPainter>

#include "domain/chess/primitives.h"

namespace View::Features::Board {
    constexpr QColor LIGHT_SQUARE_COLOR(100, 100, 100, 100);
    constexpr QColor DARK_SQUARE_COLOR(0, 0, 0, 100);
    class SquareGraphicsObject : public QGraphicsRectItem {
    public:
        explicit SquareGraphicsObject(const Domain::Types::Chess::Square square, const int size, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(parent), m_square(square), m_size(size) {
            m_rect = QRectF(0, 0, size, size);
            setZValue(1);
        }

        QRectF boundingRect() const override { return m_rect; }
        void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override {
            p->setBrush({((m_square.rank() + m_square.file()) % 2 == 0) ? LIGHT_SQUARE_COLOR : DARK_SQUARE_COLOR});
            p->drawRect(m_rect);
        }

        void setPiece(QGraphicsItem *piece) {m_piece = piece;}

        [[nodiscard]] QGraphicsItem *getPiece() const {return m_piece;}
        [[nodiscard]] QGraphicsItem *popPiece() {
            const auto piece = m_piece;
            m_piece = nullptr;
            return piece;
        }

        [[nodiscard]] Domain::Types::Chess::Square getSquare() const {return m_square;}
        void setHighlighted(const bool highlighted) {m_highlighted = highlighted;}

    signals:
        void clicked(const Domain::Types::Chess::Square &square);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
            // emit clicked(m_square);
            QGraphicsRectItem::mousePressEvent(event);
        }
    private:
        Domain::Types::Chess::Square m_square;
        int m_size;
        QRectF m_rect;
        QGraphicsItem *m_piece = nullptr;
        bool m_selected = false;
        bool m_highlighted = false;
    };
}

#endif //CHESSREPO_SQUARE_GRAPHICS_ITEM_H
