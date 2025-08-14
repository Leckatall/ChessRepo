//
// Created by Lecka on 14/08/2025.
//

#ifndef CHESSREPO_REPERTOIRE_H
#define CHESSREPO_REPERTOIRE_H
#include <qdatetime.h>

namespace Models {
    struct Move;
    struct Position;
    class FEN;

    struct RepertoireInfo {
        QString name;
        bool forWhite{true};
        QString description;
        QString author;
        QDateTime createdAt;

        RepertoireInfo(QString name_, const bool forWhite_, QString description_ = "", QString author_ = "")
            : name(std::move(name_)),
              forWhite(forWhite_),
              description(std::move(description_)),
              author(std::move(author_)),
              createdAt(QDateTime::currentDateTime()) {
        }

        RepertoireInfo() : name("") {
        }

        [[nodiscard]] bool isEmpty() const { return name.isEmpty(); }


    };

    class RepertoireMoves {
    public:
        QMap<FEN, Position> positions{};

        void addMove(const FEN &fromPosition, const Move &move, const FEN &toPosition,
                     const QString &comment = QString());

        [[nodiscard]] Move getRecommendedMove(const FEN &position) const;

        bool operator==(const RepertoireMoves & other) const {
            return positions == other.positions;
        }
    };

    struct Repertoire {
        RepertoireInfo header;
        RepertoireMoves move_db;

        [[nodiscard]] bool operator==(const Repertoire &other) const {
            if (this->header.name != other.header.name) {
                return false;
            }
            if (this->header.forWhite != other.header.forWhite) {
                return false;
            }
            if (this->header.description != other.header.description) {
                return false;
            }
            if (this->header.author != other.header.author) {
                return false;
            }
            if (this->header.createdAt != other.header.createdAt) {
                return false;
            }
            if (this->move_db != other.move_db) {
                return false;
            }
            return true;
        }
    };
} // Models

#endif //CHESSREPO_REPERTOIRE_H
