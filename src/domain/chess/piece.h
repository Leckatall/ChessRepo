//
// Created by Lecka on 23/09/2025.
//

#ifndef CHESSREPO_PIECE_H
#define CHESSREPO_PIECE_H
#include "primitives.h"

namespace Domain::Types::Chess {
    enum class PieceType {
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
        BlackKing,
        None
    };

    inline PieceType PieceTypeFactory(const std::string &piece_str) {
        std::unordered_map<std::string, PieceType> lib_to_domain{
            {"P", PieceType::WhitePawn},
                {"N", PieceType::WhiteKnight},
                {"B", PieceType::WhiteBishop},
                {"R", PieceType::WhiteRook},
                {"Q", PieceType::WhiteQueen},
                {"K", PieceType::WhiteKing},
                {"p", PieceType::BlackPawn},
                {"n", PieceType::BlackKnight},
                {"b", PieceType::BlackBishop},
                {"r", PieceType::BlackRook},
                {"q", PieceType::BlackQueen},
                {"k", PieceType::BlackKing},
                {".", PieceType::None}
        };
        return lib_to_domain.at(piece_str);
    }

    struct PieceData {
        PieceType type{};
        Square square{};
    };
}


#endif //CHESSREPO_PIECE_H