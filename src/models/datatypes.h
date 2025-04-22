//
// Created by Lecka on 04/04/2025.
//

#ifndef DATATYPES_H
#define DATATYPES_H
#include <qdatetime.h>
#include <qmetatype.h>
#include <QRegularExpression>
#include <QString>
#include <utility>
#include "chess.hpp"


namespace Models {
    inline QString formatPercentage(double value, int precision = 2) {
        return QString::number(value * 100, 'f', precision) + "%";
    }

    class UCIMove : public QString {
    public:
        explicit UCIMove(const QString &move = QString()) : QString(move) {
            if (!isValid(move)) {
                throw std::invalid_argument("Invalid UCI move");
            }
        }

        [[nodiscard]] static bool isValid(const QString &move) {
            if (move.isEmpty()) return false;
            static const QRegularExpression uciFormat("^[a-h][1-8][a-h][1-8][nbrq]?$");
            return uciFormat.match(move).hasMatch();
        }

        [[nodiscard]] QString from() const { return left(2); }
        [[nodiscard]] QString to() const { return mid(2, 2); }
        [[nodiscard]] QString promotion() const { return right(1); }
    };

    class FEN : public QString {
    public:
        explicit FEN(const QString &fen = QString()) : QString(fen) {
            if (!isValid(fen)) {
                throw std::invalid_argument("Invalid FEN string");
            }
        }

        static FEN startingPosition() {
            return FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        }

        static FEN emptyBoard() {
            return FEN("8/8/8/8/8/8/8/8 w - - 0 1");
        }

        [[nodiscard]] static bool isValid(const QString &fen) {
            // Basic FEN validation
            if (fen.isEmpty()) return false;

            // Count fields
            QStringList fields = fen.split(' ');
            if (fields.size() != 6) return false;

            // Check piece placement field
            if (const QStringList ranks = fields[0].split('/'); ranks.size() != 8) return false;

            // More validation could be added...
            return true;
        }
    };

    struct OpeningPosition {
        FEN position;
        UCIMove recommendedMove; // The move we want to play from this FEN
        QMap<UCIMove, FEN> responses;
        // A mapping of the UCIMoves our opponent could make (after we play the recommended move) to the resulting FEN
        int wins{0};
        int draws{0};
        int losses{0};
        int timesPlayed{0};
        QString comment;
        QDateTime lastPlayed;
        QDateTime createdAt{QDateTime::currentDateTime()};

        explicit OpeningPosition(FEN pos = FEN::startingPosition())
            : position(std::move(pos)) {
        }
    };

    struct OpeningRepertoire {
        QString name;
        bool forWhite{true};
        QString description;
        QString author;
        QDateTime createdAt;

        QMap<FEN, OpeningPosition> positions{};

        OpeningRepertoire(QString name_, const bool forWhite_, QString description_ = "", QString author_ = "")
            : name(std::move(name_)),
              forWhite(forWhite_),
              description(std::move(description_)),
              author(std::move(author_)),
              createdAt(QDateTime::currentDateTime()) {
        }

        OpeningRepertoire(): name("") {
        }

        [[nodiscard]] bool isEmpty() const {
            return name == "";
        }

        void addMove(const FEN &fromPosition, const UCIMove &move, const FEN &toPosition,
                     const QString &comment = QString()) {
            // Update or create the 'from' position
            auto &pos = positions[fromPosition];
            pos.position = fromPosition;
            pos.recommendedMove = move;
            pos.responses[move] = toPosition;
            if (!comment.isEmpty()) {
                pos.comment = comment;
            }

            // Ensure the 'to' position exists in our repertoire
            if (!positions.contains(toPosition)) {
                positions[toPosition] = OpeningPosition(toPosition);
            }
        }

        [[nodiscard]] bool hasPosition(const FEN &fen) const {
            return positions.contains(fen);
        }

        [[nodiscard]] QString getRecommendedMove(const FEN &position) const {
            auto it = positions.find(position);
            if (it != positions.end()) {
                return it->recommendedMove;
            }
            return {};
        }
    };

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
            return QString("Total games: %1\nWhite wins: %2 (%3)\nDraws: %4 (%5)\nBlack wins: %6 (%7)")
                    .arg(games)

                    .arg(white_wins)
                    .arg(formatPercentage(white_wr()))

                    .arg(draws)
                    .arg(formatPercentage(draw_rate()))

                    .arg(black_wins)
                    .arg(formatPercentage(black_wr()));
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
