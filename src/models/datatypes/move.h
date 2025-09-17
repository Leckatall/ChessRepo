//
// Created by Lecka on 14/08/2025.
//

#ifndef CHESSREPO_MOVE_H
#define CHESSREPO_MOVE_H
#include "chess_primitives.h"
#include "position.h"

namespace Models {
    struct Move {
        UCIMove uci;
        QString san;

        Move() = default;

        Move(const QString &uci_str,
                      const QString &san_str)
            : uci(uci_str),
              san(san_str) {
        }

        [[nodiscard]] QString toString() const { return san + " (" + uci + ")"; }

        bool operator==(const Move &other) const {
            if (uci != other.uci) {
                return false;
            }
            if (san != other.san) {
                return false;
            }
            return true;
        }

        bool operator<(const Move &other) const {
            return uci < other.uci;
        }
    };

    struct MoveData {
        Move move;
        PositionStats position_data;

        MoveData(Move move_struct, PositionStats position)
            : move(std::move(move_struct)),
              position_data(std::move(position)) {
        }
    };
} // Models

Q_DECLARE_METATYPE(Models::MoveData);




#endif //CHESSREPO_MOVE_H
