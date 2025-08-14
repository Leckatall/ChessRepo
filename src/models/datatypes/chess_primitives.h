//
// Created by Lecka on 14/08/2025.
//

#ifndef CHESSREPO_CHESS_PRIMITIVES_H
#define CHESSREPO_CHESS_PRIMITIVES_H
#include <QList>
#include <QRegularExpression>
#include <QString>

namespace Models {
    struct Position;

    class UCIMove : public QString {
    public:
        UCIMove() = default;

        explicit UCIMove(const QString &move) : QString(move) {
            if (!isValid(move)) {
                throw std::invalid_argument("Invalid UCI move");
            }
        }

        [[nodiscard]] static bool isValid(const QString &move);

        [[nodiscard]] QString from() const { return left(2); }
        [[nodiscard]] QString to() const { return mid(2, 2); }
        [[nodiscard]] QString promotion() const { return right(1); }
    };

    class FEN : public QString {
    public:
        explicit FEN(const QString &fen = QString()) : QString(fen) {
            if (!isValid(fen)) {
                throw std::invalid_argument("Invalid FEN string");
            }
        }

        static FEN startingPosition() { return FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); }

        static FEN emptyBoard() { return FEN("8/8/8/8/8/8/8/8 w - - 0 1"); }

        [[nodiscard]] static bool isValid(const QString &fen);
    };


} // Models
Q_DECLARE_METATYPE(Models::UCIMove);

Q_DECLARE_METATYPE(Models::Move);

Q_DECLARE_METATYPE(Models::MoveInfo);

#endif //CHESSREPO_CHESS_PRIMITIVES_H
