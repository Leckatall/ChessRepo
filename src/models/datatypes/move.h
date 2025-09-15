#ifndef MODELS_MOVE_H
#define MODELS_MOVE_H


#include "chess_primitives.h"
#include "position.h"

namespace Models { struct Position; } 

namespace Models {

struct Move {
    UCIMove uci;

    QString san;

    Move() = default;

    inline Move(const QString & uci_str, const QString & san_str) : uci(uci_str),
                  san(san_str) {
            };

    inline QString toString() const { return san + " (" + uci + ")"; };

    inline bool operator ==(const Move & other) const {
                if (uci != other.uci) {
                    return false;
                }
                if (san != other.san) {
                    return false;
                }
                return true;
            };

    inline bool operator <(const Move & other) const {
                return uci < other.uci;
            };

};
struct MoveEdge {
    Move move;

    Position * result;

    QString comment;

    inline MoveEdge(Move m, Position * p, QString c = {}) : move(std::move(m)), result(p), comment(std::move(c)) {
            };

    inline bool operator ==(const MoveEdge & other) const {
                return move == other.move;
            };

};
struct MoveData {
    Move move;

    PositionStats stats;

    inline MoveData(Move move_struct, PositionStats position) : move(std::move(move_struct)),
                  stats(std::move(position)) {
            };

};

} // namespace Models
#endif
