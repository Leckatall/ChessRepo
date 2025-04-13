//
// Created by Lecka on 06/04/2025.
//

#ifndef OPENINGREPERTOIREMODEL_H
#define OPENINGREPERTOIREMODEL_H
#include <qdatetime.h>
#include <QString>

#include "datatypes.h"

namespace Models {
    struct OpeningRepertoir {
        QString name;
        bool forWhite{};
        QDateTime created;
        QString createdBy;
        QMap<FEN, OpeningPosition> positions;

        OpeningRepertoir(const QString& name_, const bool forWhite_)
        : name(name_)
        , forWhite(forWhite_)
        , created(QDateTime::currentDateTime())
        , createdBy("Leckatall")
        {
            // Add starting position
            OpeningPosition startPos;
            positions[startPos.position] = startPos;
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
} // models

#endif //OPENINGREPERTOIREMODEL_H
