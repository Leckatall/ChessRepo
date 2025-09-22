//
// Created by Lecka on 21/09/2025.
//

#include "test_utils.h"

namespace Test::Utils {
    Domain::Types::MoveData createTestMoveData() {
        return {{"a2a4"}, {10, 4, 2, 4}};
    }

    Domain::Types::Repertoire::RepertoireData createHeaderOnlyRepertoire() {
        Domain::Types::Repertoire::RepertoireData repertoire;
        repertoire.header.name = "Test Repertoire";
        repertoire.header.forWhite = true;
        repertoire.header.author = "Test Author";
        repertoire.header.description = "Test Description";
        repertoire.header.createdAt = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
        return repertoire;
    }

    Domain::Types::Repertoire::RepertoireData createTestRepertoire() {
        Domain::Types::Repertoire::RepertoireData repertoire(createHeaderOnlyRepertoire());
        Domain::Types::PositionNode node{Domain::Types::PositionKey(Domain::Types::FEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1")), {10, 4, 2, 4}};
        repertoire.data.addEdge(repertoire.data.getRootKey(), node, Domain::Types::UCIMove("e2e4"), "");
        return repertoire;
    }
}

