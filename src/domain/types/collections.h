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
        MoveData(const UCIMove &uci, const PositionStats &stats) : uci(uci), stats(stats) {}
    };
}


#endif //CHESSREPO_COLLECTIONS_H