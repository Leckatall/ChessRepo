//
// Created by Lecka on 20/09/2025.
//

#include "test_board_widget.h"

#include <qboxlayout.h>

namespace Test {
    void TestBoardWidget::initTestCase() {
        m_boardViewModel = new Presentation::Features::Board::BoardViewModel(m_board, this);
        m_window = new QMainWindow();
        m_board_view = new View::Features::Board::BoardGraphicsView(m_boardViewModel->scene(), m_window);
        m_info_label = new QLabel("Info Label", m_window);
        m_boardViewModel->updateScene();
        QWidget *central_widget = new QWidget(m_window);
        m_window->setCentralWidget(central_widget);
        auto layout = new QVBoxLayout(central_widget);
        layout->addWidget(m_board_view);
        layout->addWidget(m_info_label);
        m_board_view->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        m_window->setGeometry(500, 500, 500, 500);
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
}


QTEST_MAIN(Test::TestBoardWidget)
#include "moc_test_board_widget.cpp"
