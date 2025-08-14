//
// Created by Lecka on 14/08/2025.
//

#include "repertoire.h"

#include "position.h"


namespace Models {
    void RepertoireMoves::addMove(const FEN &fromPosition, const Move &move, const FEN &toPosition,
        const QString &comment) {
        // Ensure the 'to' position exists in our repertoire
        if (!positions.contains(toPosition)) {
            positions[toPosition] = Position(toPosition);
        }
        // Update or create the 'from' position
        positions[fromPosition].moves.append(MoveEdge(move, &positions[toPosition], comment));
    }

    Move RepertoireMoves::getRecommendedMove(const FEN &position) const {
        auto it = positions.find(position);
        if (it != positions.end() && !it->moves.isEmpty()) {
            return it->moves.first().move;
        }
        return {};
    }
} // Models
