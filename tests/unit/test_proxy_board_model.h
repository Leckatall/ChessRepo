//
// Created by Lecka on 22/09/2025.
//

#ifndef CHESSREPO_TEST_PROXY_BOARD_MODEL_H
#define CHESSREPO_TEST_PROXY_BOARD_MODEL_H
#include <QtTest/QtTest>

#include "board_controller.h"

namespace Test {
    class TestProxyBoardModel: public QObject {
        Q_OBJECT
    private slots:
        void initTestCase();        // Runs once before all tests
        void cleanupTestCase();     // Runs once after all tests


        void init();                // Runs before each test
        void cleanup();             // Runs after each test

        void testSquareToIndex();
        void testIndexToSquare();

    private:
        chessboard::TblModel* m_model;
        chessboard::ProxyTblModel* m_proxyModel;
        QMap<Domain::Types::Chess::Square, QModelIndex*> test_white_on_bottom_squares;;
        QMap<Domain::Types::Chess::Square, QModelIndex*> test_black_on_bottom_squares;;
    };
}



#endif //CHESSREPO_TEST_PROXY_BOARD_MODEL_H