
#include "position.h"
#include "move.h"

namespace Models {

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

bool Position::operator ==() const {

        if (this->fen != other.fen) {
            return false;
        }
        if (this->moves != other.moves) {
            return false;
        }
        return true;
}


} // namespace Models
