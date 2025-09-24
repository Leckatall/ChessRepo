//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_PRIMITIVES_H
#define CHESSREPO_PRIMITIVES_H
#include <qmetatype.h>

#include "chess.hpp"

namespace Domain::Types::Chess {
    struct Square {
        int m_id = 64; // NULL MOVE

        int rank() const {return (m_id / 8) + 1;}

        int file() const {return (m_id % 8) + 1;}

        Square() = default;

        Square(const int file, const int rank): m_id(((rank - 1) * 8) + (file - 1)) {
        }

        explicit Square(const int id): m_id(id) {
        }
        bool operator==(const Square &other) const {
            return m_id == other.m_id;
        }
        bool operator<(const Square &other) const {
            return m_id < other.m_id;
        }

        operator bool() const {
            return m_id != 0;
        }
        Square(const chess::Square square) { m_id = square.index();}
        chess::Square toChessLib() const {return chess::Square(chess::File(file()), chess::Rank(rank()));}
    };
    struct Move {
        Square from;
        Square to;
        Move() = default;
        Move(const Square &from, const Square &to): from(from), to(to) {
        }
        chess::Move toChessLib() const { return chess::Move::make(from.toChessLib(), to.toChessLib());}
    };
}
namespace std {
    template<> struct hash<Domain::Types::Chess::Square> {
        size_t operator()(const Domain::Types::Chess::Square &k) const noexcept {
            return hash<int>{}(k.file()) ^ hash<int>{}(k.rank());
        }
    };
    template<> struct hash<Domain::Types::Chess::Move> {
        size_t operator()(const Domain::Types::Chess::Move &k) const noexcept {
            return hash<Domain::Types::Chess::Square>{}(k.from) ^ hash<Domain::Types::Chess::Square>{}(k.to);
        }
    };

}
Q_DECLARE_METATYPE(Domain::Types::Chess::Square)
Q_DECLARE_METATYPE(Domain::Types::Chess::Move)

#endif //CHESSREPO_PRIMITIVES_H