//
// Created by Lecka on 13/06/2025.
//

#include "repertoire_navigator.h"

// QList<RepertoireLine> RepertoireNavigator::getLines(const Models::Repertoire &rep) {
//
// }
//
// void RepertoireNavigator::generateLines(const Models::FEN &pos, RepertoireLine &current, QList<RepertoireLine> &lines) {
//     auto it = rep.positions.find(pos);
//     if (it == rep.positions.end()) {
//         if (!current.moves.isEmpty()) {
//             lines.append(current);
//         }
//         return;
//     }
//
//     const auto& opening_pos = it.value();
//
//     // Add our move
//     MovePair our_move{
//         pos,
//         opening_pos.recommendedMove,
//         opening_pos.position,  // Position after our move
//         true
//     };
//     current.moves.append(our_move);
//
//     // Add each possible response and recurse
//     for (auto [response_move, next_pos] : opening_pos.responses.asKeyValueRange()) {
//         Line branch = current;
//         MovePair their_move{
//             our_move.resulting_position,
//             response_move,
//             next_pos,
//             false
//         };
//         branch.moves.append(their_move);
//         generateLines(next_pos, branch, lines, rep);
//     }
// }
