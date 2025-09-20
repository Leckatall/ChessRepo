//
// Created by Lecka on 19/09/2025.
//

#include "board_graphics_scene.h"

#include "piece_graphics_item.h"
#include "square_graphics_item.h"

enum class PieceTypeFake {
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

namespace View::Features::Board {
    BoardGraphicsScene::BoardGraphicsScene(QObject *parent)
        : QGraphicsScene(parent){
        m_square_size = std::min(width() / 8, height() / 8);
        m_piece_svg_cache.reserve(12);
        cache_piece(PieceType::WhitePawn, "w_pawn");
        cache_piece(PieceType::WhiteKnight, "w_knight");
        cache_piece(PieceType::WhiteBishop, "w_bishop");
        cache_piece(PieceType::WhiteRook, "w_rook");
        cache_piece(PieceType::WhiteQueen, "w_queen");
        cache_piece(PieceType::WhiteKing, "w_king");
        cache_piece(PieceType::BlackPawn, "b_pawn");
        cache_piece(PieceType::BlackKnight, "b_knight");
        cache_piece(PieceType::BlackBishop, "b_bishop");
        cache_piece(PieceType::BlackRook, "b_rook");
        cache_piece(PieceType::BlackQueen, "b_queen");
        cache_piece(PieceType::BlackKing, "b_king");
    }

    void BoardGraphicsScene::update_board(const QList<PieceData> &pieces) {
        for (auto &piece_data : pieces) {
            PieceGraphicsItem piece_item(m_piece_svg_cache[piece_data.type], m_square_size, m_squares[piece_data.square]);
        }
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

    void BoardGraphicsScene::on_piece_dragged(const QPointF &origin, const QPointF &target) {
        emit requestMove(Domain::Types::Chess::Move(point_to_square(origin), point_to_square(target)));
    }

    void BoardGraphicsScene::init_board() {
        for (int squareid = 0; squareid < 64; squareid++) {
            const Domain::Types::Chess::Square square(squareid);
            auto square_item = new SquareGraphicsObject(square, m_square_size);
            connect(square_item, &SquareGraphicsObject::clicked,
                this, [this, square] {emit squareClicked(square);});
            m_squares.insert(square, square_item);
        }
    }

    void BoardGraphicsScene::cache_piece(const PieceType type, const QString &file_name) {
        m_piece_svg_cache[type] = QSharedPointer<QSvgRenderer>::create(m_svg_path + file_name + ".svg", this);
    }

    Domain::Types::Chess::Square BoardGraphicsScene::point_to_square(const QPointF point) const {

    }
}
