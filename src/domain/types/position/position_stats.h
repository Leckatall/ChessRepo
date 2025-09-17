//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_POSITION_STATS_H
#define CHESSREPO_POSITION_STATS_H
#include <cstdint>

namespace Domain::Types {
    struct PositionStats {
        std::int64_t games = 0;
        std::int64_t white_wins = 0;
        std::int64_t draws = 0;
        std::int64_t black_wins = 0;

        // helper methods
        [[nodiscard]] double white_wr() const {
            return games > 0 ? static_cast<double>(white_wins) / games : 0.0;
        }

        [[nodiscard]] double black_wr() const {
            return games > 0 ? static_cast<double>(black_wins) / games : 0.0;
        }

        [[nodiscard]] double draw_rate() const {
            return games > 0 ? static_cast<double>(draws) / games : 0.0;
        }
    };
}
#endif //CHESSREPO_POSITION_STATS_H
