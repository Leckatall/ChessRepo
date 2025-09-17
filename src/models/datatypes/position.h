//
// Created by Lecka on 14/08/2025.
//

#ifndef CHESSREPO_POSITION_H
#define CHESSREPO_POSITION_H
#include <qdatetime.h>

#include "chess_primitives.h"

namespace Models {
    struct OpeningTitle {
        QString eco;
        QString name;

        OpeningTitle(QString eco_str, QString name_str) : eco(std::move(eco_str)), name(std::move(name_str)) {
        }

        OpeningTitle() = default;

        explicit operator bool() const { return !(eco.isEmpty() and name.isEmpty()); }
    };

    struct PositionStats {
        std::int64_t games{};
        std::int64_t white_wins{};
        std::int64_t draws{};
        std::int64_t black_wins{};
        OpeningTitle opening{};

        PositionStats(std::int64_t g, std::int64_t w, std::int64_t d, std::int64_t b,
                      OpeningTitle o = {});

        PositionStats() = default;

        // helper methods
        [[nodiscard]] double win_rate(const std::int64_t wins) const {
            return games > 0 ? static_cast<double>(wins) / static_cast<double>(games) : 0.0;
        }

        [[nodiscard]] double white_wr() const { return win_rate(white_wins); }

        [[nodiscard]] double black_wr() const { return win_rate(black_wins); }

        [[nodiscard]] double draw_rate() const { return win_rate(draws); }

        [[nodiscard]] QString toToolTip() const;
    };

    struct PositionInfo {
        QString comment;
        QDateTime lastPlayed;
        QDateTime createdAt{QDateTime::currentDateTime()};
        PositionStats user_stats; // W/L of the user
        PositionStats api_stats; // W/L from the API
    };

} // Models

#endif //CHESSREPO_POSITION_H
