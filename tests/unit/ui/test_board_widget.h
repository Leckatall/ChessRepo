//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_TEST_BOARD_WIDGET_H
#define CHESSREPO_TEST_BOARD_WIDGET_H

#include <QMainWindow>
#include <QtTest/QtTest>

#include "components/chessboard/board_graphics_view.h"
#include "components/explorer/explorer_view.h"
#include "viewmodels/board_viewmodel.h"
namespace Test {
    class TestBoardWidget : public QObject {
        Q_OBJECT

    private slots:
        void initTestCase(); // Runs once before all tests
        void cleanupTestCase(); // Runs once after all tests
        void init(); // Runs before each test
        void cleanup(); // Runs after each test

        void testBoardRenders();
        void testBoardCanRenderFENs();
        void testBoardFlips();
        void testBoardMoves();
        void testBoardUndo();
        void testBoardEmitsSquareClicked();
        void testBoardSelectsSquare();
        void testBoardEmitsMoveRequest();
        void testBoardRequestLegalTargets();
        void testBoardHighlightsLegalTargets();
        void testBoardHighlightsSelectedSquare();
        void testDraggingPieces();
        void testDrawingArrows();


    private:
        Domain::Features::Chess::Board m_board{};
        Presentation::Features::Board::BoardViewModel* m_boardViewModel;
        QMainWindow *m_window;
        View::Features::Board::BoardGraphicsView *m_board_view;
        QLabel *m_info_label;

    };
}



#endif //CHESSREPO_TEST_BOARD_WIDGET_H