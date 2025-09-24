//
// Created by Lecka on 23/09/2025.
//

#ifndef CHESSREPO_PIECE_H
#define CHESSREPO_PIECE_H
#include "primitives.h"

namespace Domain::Types::Chess {
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
        PieceType type{};
        Square square{};
    };
}


#endif //CHESSREPO_PIECE_H