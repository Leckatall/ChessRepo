//
// Created by Lecka on 21/09/2025.
//

#ifndef CHESSREPO_TEST_UTILS_H
#define CHESSREPO_TEST_UTILS_H
#include "repertoire/repertoire.h"
#include "types/collections.h"

namespace Test::Utils {
    Domain::Types::MoveData createTestMoveData();
    Domain::Types::Repertoire::RepertoireData createHeaderOnlyRepertoire();

    Domain::Types::Repertoire::RepertoireData createTestRepertoire();
}



#endif //CHESSREPO_TEST_UTILS_H