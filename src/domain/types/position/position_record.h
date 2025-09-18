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

    struct PositionRecord {
        PositionKey key;
        PositionStats stats;
        StatsSource source;
        std::string tag;
    };
}
#endif //CHESSREPO_POSITION_AGGREGATE_H