//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_TEST_BOARD_VIEWMODEL_H
#define CHESSREPO_TEST_BOARD_VIEWMODEL_H
#include <QtTest/QtTest>

#include "viewmodels/board_viewmodel.h"

class TestBoardViewModel : public QObject {
    Q_OBJECT

private slots:
    void initTestCase(); // Runs once before all tests
    void cleanupTestCase(); // Runs once after all tests
    void init(); // Runs before each test
    void cleanup(); // Runs after each test

    void testSquareToPointConsistentWithPointToSquare();
    void testSetFenUpdatesBoard();
    void testMakeMoveUpdatesBoard();
    void testUndoMoveRevertsBoard();
    void testOnSquareClickedSelectsSquare();
    void testOnSquareClickedEmitsSignal();
    void testFlipBoardChangesOrientation();
    void testSceneResizedUpdatesSquareSize();


private:
    Presentation::Features::Board::BoardViewModel* m_boardViewModel;
    Domain::Features::Chess::Board m_board{};
};
#endif //CHESSREPO_TEST_BOARD_VIEWMODEL_H