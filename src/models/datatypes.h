//
// Created by Lecka on 04/04/2025.
//

#ifndef DATATYPES_H
#define DATATYPES_H
#include <qmetatype.h>
#include <QString>


namespace Models {
    struct Opening {
        QString eco;
        QString name;

        Opening(QString eco_str, QString name_str): eco(std::move(eco_str)), name(std::move(name_str)) {
        }

        Opening() = default;

        explicit operator bool() const { return !(eco.isEmpty() and name.isEmpty()); }
    };

    struct PositionData {
        std::int64_t games{};
        std::int64_t white_wins{};
        std::int64_t draws{};
        std::int64_t black_wins{};
        Opening opening;

        PositionData(const std::int64_t g, const std::int64_t w, const std::int64_t d, const std::int64_t b,
                     Opening o = {})
            : games(g),
              white_wins(w),
              draws(d),
              black_wins(b),
              opening(std::move(o)) {
        }
        PositionData() = default;

        // helper methods
        [[nodiscard]] double white_wr() const {
            return games > 0 ? static_cast<double>(white_wins) / static_cast<double>(games) : 0.0;
        }

        [[nodiscard]] double black_wr() const {
            return games > 0 ? static_cast<double>(black_wins) / static_cast<double>(games) : 0.0;
        }

        [[nodiscard]] double draw_rate() const {
            return games > 0 ? static_cast<double>(draws) / static_cast<double>(games) : 0.0;
        }

        [[nodiscard]] QString toToolTip() const {
            return QString("Total games: %1\nWhite wins: %2%\nDraws: %3%\nBlack wins: %4%")
                .arg(games)
                .arg(white_wr() * 100.0, 0, 'f', 1)
                .arg(draw_rate() * 100.0, 0, 'f', 1)
                .arg(black_wr() * 100.0, 0, 'f', 1);
        }
    };

    struct MoveData {
        QString uci;
        QString san;
        PositionData position_data;

        MoveData(QString uci_str, QString san_str, PositionData position)
            : uci(std::move(uci_str)),
              san(std::move(san_str)),
              position_data(std::move(position)) {
        }
    };
}

Q_DECLARE_METATYPE(Models::MoveData);
Q_DECLARE_METATYPE(Models::PositionData);

#endif //DATATYPES_H
