//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_POSITION_AGGREGATE_H
#define CHESSREPO_POSITION_AGGREGATE_H
#include "position_key.h"
#include "position_stats.h"

// Might not be needed
namespace Domain::Types {
    enum class StatsSource { LocalRepertoire, OnlineExplorer, EngineEval };

    struct PositionAggregate {
        PositionKey key;
        PositionStats stats;      // the stats snapshot for a given source
        StatsSource source;       // where the stats came from
        std::string tag;          // optional context (e.g., time control, date range)
    };
}
#endif //CHESSREPO_POSITION_AGGREGATE_H