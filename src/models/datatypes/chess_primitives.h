#ifndef MODELS_CHESS_PRIMITIVES_H
#define MODELS_CHESS_PRIMITIVES_H


namespace Models {

typedef QString typedef35;
class UCIMove : public typedef35 {
  public:
    UCIMove() = default;

    inline explicit UCIMove(const QString & move) : QString(move) {
                if (!isValid(move)) {
                    throw std::invalid_argument("Invalid UCI move");
                }
            };

    static bool isValid(const QString & move);

    inline QString from() const { return left(2); };

    inline QString to() const { return mid(2, 2); };

    inline QString promotion() const { return right(1); };

};
class FEN : public typedef35 {
  public:
    inline explicit FEN(const QString & fen = QString()) : QString(fen) {
                if (!isValid(fen)) {
                    throw std::invalid_argument("Invalid FEN string");
                }
            };

    static inline FEN startingPosition() { return FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); };

    static inline FEN emptyBoard() { return FEN("8/8/8/8/8/8/8/8 w - - 0 1"); };

    static bool isValid(const QString & fen);

};

} // namespace Models
#endif
