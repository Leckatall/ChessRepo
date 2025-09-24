//
// Created by Lecka on 19/09/2025.
//

#include "board_graphics_scene.h"

#include "piece_graphics_item.h"
#include "square_graphics_item.h"
#include "chess/piece.h"

namespace View::Features::Board {
    BoardGraphicsScene::BoardGraphicsScene(QObject *parent)
        : QGraphicsScene(parent){
        m_square_size = 20;
        m_piece_svg_cache.reserve(12);
        cachePiece(Domain::Types::Chess::PieceType::WhitePawn, "w_pawn");
        cachePiece(Domain::Types::Chess::PieceType::WhiteKnight, "w_knight");
        cachePiece(Domain::Types::Chess::PieceType::WhiteBishop, "w_bishop");
        cachePiece(Domain::Types::Chess::PieceType::WhiteRook, "w_rook");
        cachePiece(Domain::Types::Chess::PieceType::WhiteQueen, "w_queen");
        cachePiece(Domain::Types::Chess::PieceType::WhiteKing, "w_king");
        cachePiece(Domain::Types::Chess::PieceType::BlackPawn, "b_pawn");
        cachePiece(Domain::Types::Chess::PieceType::BlackKnight, "b_knight");
        cachePiece(Domain::Types::Chess::PieceType::BlackBishop, "b_bishop");
        cachePiece(Domain::Types::Chess::PieceType::BlackRook, "b_rook");
        cachePiece(Domain::Types::Chess::PieceType::BlackQueen, "b_queen");
        cachePiece(Domain::Types::Chess::PieceType::BlackKing, "b_king");
        initBoard();
    }

    void BoardGraphicsScene::updateBoard(const QList<Domain::Types::Chess::PieceData> &pieces) {
        for (const auto &[type, square] : pieces) {
            m_squares[square]->setPiece(m_piece_svg_cache[type]);
        }
    }

    void BoardGraphicsScene::setSelectedSquare(Domain::Types::Chess::Square *square) {
        if (m_selected_square) m_squares[*m_selected_square]->setHighlighted(false);
        m_selected_square = square;
        if (m_selected_square) m_squares[*m_selected_square]->setHighlighted(true);
        update();
    }

    void BoardGraphicsScene::onPieceDragged(const QPointF &origin, const QPointF &target) {
        // emit requestMove(Domain::Types::Chess::Move(point_to_square(origin), point_to_square(target)));
    }

    void BoardGraphicsScene::setSquareSize(const int size) {
        qDebug() << "Setting square size to: " << size;
        m_square_size = size;
        for (const auto &square_item : m_squares) {
            square_item->setSize(m_square_size);
            square_item->setPos((square_item->getSquare().file() - 1) * m_square_size, (8 - square_item->getSquare().rank()) * m_square_size);
        }
    }

    void BoardGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
        auto items = this->items(event->scenePos());
        int file = static_cast<int>(event->scenePos().x() / m_square_size) + 1;
        int rank = 8 - static_cast<int>(event->scenePos().y() / m_square_size);
        qDebug() << "Mouse pressed at: " << event->scenePos() << " File: " << file << " Rank: " << rank;
        emit squareClicked({file, rank});
        QGraphicsScene::mousePressEvent(event);
    }

    // DEPRECATED
    // void BoardGraphicsScene::on_square_clicked(Domain::Types::Chess::Square square) {
    //     if (m_selected_square) {
    //         if (m_legal_moves[m_selected_square].contains(square)) {
    //             emit requestMove(Domain::Types::Chess::Move(m_selected_square, square));
    //         }
    //         m_selected_square = {};
    //         return;
    //     }
    //     m_selected_square = square;
    // }

    void BoardGraphicsScene::initBoard() {
        for (int squareid = 0; squareid < 64; squareid++) {
            const Domain::Types::Chess::Square square(squareid);
            auto square_item = new SquareGraphicsObject(square, m_square_size);
            addItem(square_item);
            m_squares.insert(square, square_item);
        }
        setSquareSize(20);
    }

    void BoardGraphicsScene::cachePiece(const Domain::Types::Chess::PieceType type, const QString &file_name) {
        m_piece_svg_cache[type] = QSharedPointer<QSvgRenderer>::create(m_svg_path + file_name + ".svg", this);
    }
}
