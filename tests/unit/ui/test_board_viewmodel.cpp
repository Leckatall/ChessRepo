//
// Created by Lecka on 20/09/2025.
//

#include "test_board_viewmodel.h"

void TestBoardViewModel::initTestCase() {
    m_boardViewModel = new Presentation::Features::Board::BoardViewModel(m_board, this);
}

void TestBoardViewModel::cleanupTestCase() {
    delete m_boardViewModel;
}

void TestBoardViewModel::init() {
    m_boardViewModel->setFen(Domain::Types::FEN::startingPosition());
}

void TestBoardViewModel::cleanup() {
}

void TestBoardViewModel::testSquareToPointConsistentWithPointToSquare() {
    for (int file = 0; file < 8; file++) {
        for (int rank = 1; rank <= 8; rank++) {
            Domain::Types::Chess::Square square(file, rank);
            QPointF point = m_boardViewModel->squareToPoint(square);
            Domain::Types::Chess::Square converted_back = m_boardViewModel->pointToSquare(point);
            QCOMPARE(square, converted_back);
        }
    }
}

void TestBoardViewModel::testSetFenUpdatesBoard() {
    m_boardViewModel->setFen(Domain::Types::FEN::emptyBoard());
    QCOMPARE(m_board.fen(), Domain::Types::FEN::emptyBoard());
}

void TestBoardViewModel::testMakeMoveUpdatesBoard() {
    auto original_fen = m_boardViewModel->getFen();
    m_boardViewModel->makeMove(Domain::Types::Chess::Move(Domain::Types::Chess::Square(4, 2), Domain::Types::Chess::Square(4, 4))); // e2e4
    QVERIFY(m_boardViewModel->getFen() != original_fen);
}

void TestBoardViewModel::testUndoMoveRevertsBoard() {
    auto original_fen = m_boardViewModel->getFen();
    m_boardViewModel->makeMove(Domain::Types::Chess::Move(Domain::Types::Chess::Square(4, 2), Domain::Types::Chess::Square(4, 4))); // e2e4
    m_boardViewModel->undoMove();
    QCOMPARE(m_boardViewModel->getFen(), original_fen);
}

void TestBoardViewModel::testOnSquareClickedSelectsSquare() {

}

void TestBoardViewModel::testOnSquareClickedEmitsSignal() {

}

void TestBoardViewModel::testFlipBoardChangesOrientation() {
    auto original_square = m_boardViewModel->pointToSquare(QPoint(0, 0));
    m_boardViewModel->flipBoard();
    auto flipped_square_after_flip = m_boardViewModel->pointToSquare(QPoint(0, 0));
    auto flipped_square = Domain::Types::Chess::Square(original_square.file(), 9 - original_square.rank());
    QCOMPARE(flipped_square_after_flip, flipped_square);
}

void TestBoardViewModel::testSceneResizedUpdatesSquareSize() {
    m_boardViewModel->scene()->setSceneRect(0, 0, 200, 200);
    int original_size = m_boardViewModel->square_size();
    m_boardViewModel->scene()->setSceneRect(0, 0, 400, 400);
    QVERIFY(original_size != m_boardViewModel->square_size());
}
