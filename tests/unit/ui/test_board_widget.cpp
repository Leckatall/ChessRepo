//
// Created by Lecka on 20/09/2025.
//

#include "test_board_widget.h"

void TestBoardWidget::initTestCase() {
    m_boardViewModel = new Presentation::Features::Board::BoardViewModel(m_board, this);
    m_window = new QMainWindow();
    m_board_view = new View::Features::Board::BoardGraphicsView(m_boardViewModel, m_window);
    m_window->setGeometry(500, 500, 500, 500);
    m_window->setCentralWidget(m_board_view);
    m_window->show();
    QVERIFY(QTest::qWaitForWindowExposed(m_window, 5000));
}

void TestBoardWidget::cleanupTestCase() {
    delete m_board_view;
    delete m_window;
    delete m_boardViewModel;
}

void TestBoardWidget::init(){
    QTest::qWait(5000);
}

void TestBoardWidget::cleanup() {
}

void TestBoardWidget::testBoardRenders() {

}

void TestBoardWidget::testBoardCanRenderFENs() {

}

void TestBoardWidget::testBoardFlips() {
}

void TestBoardWidget::testBoardMoves() {
}

void TestBoardWidget::testBoardUndo() {
}

void TestBoardWidget::testBoardEmitsSquareClicked() {
}

void TestBoardWidget::testBoardSelectsSquare() {
}

void TestBoardWidget::testBoardEmitsMoveRequest() {
}

void TestBoardWidget::testBoardRequestLegalTargets() {
}

void TestBoardWidget::testBoardHighlightsLegalTargets() {
}

void TestBoardWidget::testBoardHighlightsSelectedSquare() {
}

void TestBoardWidget::testDraggingPieces() {
}

void TestBoardWidget::testDrawingArrows() {
}

QTEST_MAIN(TestBoardWidget)
#include "moc_test_board_widget.cpp"
