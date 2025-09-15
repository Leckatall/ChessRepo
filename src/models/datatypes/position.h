#ifndef MODELS_POSITION_H
#define MODELS_POSITION_H


#include "chess_primitives.h"

namespace Models { struct MoveEdge; } 

namespace Models {

struct OpeningTitle {
    QString eco;

    QString name;

    inline OpeningTitle(QString eco_str, QString name_str) : eco(std::move(eco_str)), name(std::move(name_str)) {
            };

    OpeningTitle() = default;

    inline explicit operator bool() const { return !(eco.isEmpty() and name.isEmpty()); };

};
struct PositionStats {
    std::int64_t games {};

    std::int64_t white_wins {};

    std::int64_t draws {};

    std::int64_t black_wins {};

    PositionStats(std::int64_t g, std::int64_t w, std::int64_t d, std::int64_t b);

    PositionStats() = default;

    // helper methods
    inline double white_wr() const { return win_rate(white_wins); };

    inline double black_wr() const { return win_rate(black_wins); };

    inline double draw_rate() const { return win_rate(draws); };

    QString toToolTip() const;


  private:
    inline double win_rate(const std::int64_t wins) const {
                return games > 0 ? static_cast<double>(wins) / static_cast<double>(games) : 0.0;
            };

};
struct PositionInfo {
    QString comment;

    QDateTime lastPlayed;

    QDateTime createdAt {QDateTime::currentDateTime()};

    OpeningTitle opening {};

    // W/L of the user
    PositionStats user_stats;

    // W/L from the API
    PositionStats api_stats;

};
struct Position {
    FEN fen;

    QList<MoveEdge> moves;

    // A mapping of the UCIMoves our opponent could make (after we play the recommended move) to the resulting FEN
    
    PositionInfo info;

    inline explicit Position(FEN pos = FEN::startingPosition()) : fen(std::move(pos)) {
            };

    bool operator ==(const Position & other) const;

};

} // namespace Models
#endif
