//
// Created by Lecka on 24/09/2025.
//

#include "test_square_primitive.h"

#include "chess/primitives.h"
namespace Test {
    void TestSqaurePrimitive::idToRankFile() {
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                Domain::Types::Chess::Square square((rank*8) + file);
                QCOMPARE(square.file(), file + 1);
                QCOMPARE(square.rank(), rank + 1);
            }
        }
    }

    void TestSqaurePrimitive::rankFileToId() {
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                Domain::Types::Chess::Square square(file + 1, rank+1);
                QCOMPARE(square.m_id, (rank*8) + file);
            }
        }
    }
}

QTEST_MAIN(Test::TestSqaurePrimitive)
