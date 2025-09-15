#ifndef MODELS_CHESS_PRIMITIVES_H
#define MODELS_CHESS_PRIMITIVES_H
#include <QString>


namespace Models {

class UCIMove : public QString {
  public:
    UCIMove() = default;

    explicit UCIMove(const QString & move) : QString(move) {
                if (!isValid(move)) {
                    throw std::invalid_argument("Invalid UCI move");
                }
            };

    static bool isValid(const QString & move);

    [[nodiscard]] QString from() const { return left(2); };

    [[nodiscard]] QString to() const { return mid(2, 2); };

    [[nodiscard]] QString promotion() const { return right(1); };

};
class FEN : public QString {
  public:
   explicit FEN(const QString & fen = QString()) : QString(fen) {
                if (!isValid(fen)) {
                    throw std::invalid_argument("Invalid FEN string");
                }
            };

    static FEN startingPosition() { return FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); };

    static FEN emptyBoard() { return FEN("8/8/8/8/8/8/8/8 w - - 0 1"); };

    static bool isValid(const QString & fen);

};

} // namespace Models
#endif
