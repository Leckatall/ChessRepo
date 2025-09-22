//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_COLLECTIONS_H
#define CHESSREPO_COLLECTIONS_H
#include "uci_move.h"
#include "position/position_stats.h"

namespace Domain::Types {
    struct MoveData {
        UCIMove uci;
        PositionStats stats;

        MoveData() = default;

        MoveData(const UCIMove &uci, const PositionStats &stats) : uci(uci), stats(stats) {
        }

        bool operator==(const MoveData &other) const {
            if (this->uci != other.uci) return false;
            if (this->stats != other.stats) return false;
            return true;
        }
    };
}


#endif //CHESSREPO_COLLECTIONS_H
