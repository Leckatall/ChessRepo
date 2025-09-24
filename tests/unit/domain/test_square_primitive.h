//
// Created by Lecka on 24/09/2025.
//

#ifndef CHESSREPO_TEST_SQUARE_PRIMITIVE_H
#define CHESSREPO_TEST_SQUARE_PRIMITIVE_H

#include <QtTest/QtTest>

namespace Test {
    class TestSqaurePrimitive: public QObject {
        Q_OBJECT
    private slots:
        void idToRankFile();
        void rankFileToId();
    };
}



#endif //CHESSREPO_TEST_SQUARE_PRIMITIVE_H