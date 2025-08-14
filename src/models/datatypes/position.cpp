//
// Created by Lecka on 14/08/2025.
//

#include "position.h"

#include "utils/utils.h"

namespace Models {
    PositionStats::PositionStats(const std::int64_t g, const std::int64_t w, const std::int64_t d, const std::int64_t b,
        OpeningTitle o): games(g),
                         white_wins(w),
                         draws(d),
                         black_wins(b),
                         opening(std::move(o)) {
    }

    QString PositionStats::toToolTip() const {
        return QString("Total games: %1\nWhite wins: %2 (%3)\nDraws: %4 (%5)\nBlack wins: %6 (%7)")
                .arg(games)

                .arg(white_wins)
                .arg(Utils::formatPercentage(white_wr()))

                .arg(draws)
                .arg(Utils::formatPercentage(draw_rate()))

                .arg(black_wins)
                .arg(Utils::formatPercentage(black_wr()));
    }

    bool Position::operator==(const Position &other) const {
        if (this->fen != other.fen) {
            return false;
        }
        if (this->moves != other.moves) {
            return false;
        }
        return true;
    }
} // Models