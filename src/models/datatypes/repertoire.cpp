
#include "repertoire.h"
#include "chess_primitives.h"
#include "position.h"
#include "move.h"

namespace Models {

void RepertoireMoves::addMove() {

        // Ensure the 'to' position exists in our repertoire
        if (!positions.contains(toPosition)) {
            positions[toPosition] = Position(toPosition);
        }
        // Update or create the 'from' position
        positions[fromPosition].moves.append(MoveEdge(move, &positions[toPosition], comment));
}

Move RepertoireMoves::getRecommendedMove() const {

        auto it = positions.find(position);
        if (it != positions.end() && !it->moves.isEmpty()) {
            return it->moves.first().move;
        }
        return {};
}


} // namespace Models
