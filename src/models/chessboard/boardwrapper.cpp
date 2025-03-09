//
// Created by Lecka on 07/03/2025.
//

#include "boardwrapper.h"

QSet<chess::Square> BoardWrapper::get_legal_targets_for(const chess::Square &square) const {
    QSet<chess::Square> targets = {};
    chess::Movelist moves;
    chess::movegen::legalmoves<chess::movegen::MoveGenType::ALL>(moves, *this);
    for (auto move: moves) {
        if (move.from() == square) {
            targets << move.to();
        }
    }
    return targets;
}

/**
 *
 * @param square
 * @return is there a piece of the color to move at this square
 */
bool BoardWrapper::is_enabled_square(const chess::Square &square) const {
    const chess::Piece piece = at(square);
    if(piece == chess::Piece::NONE) {
        return false;
    }
    if(piece.color() != sideToMove()) {
        return false;
    }
    return true;
}









