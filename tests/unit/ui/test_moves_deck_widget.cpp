//
// Created by Lecka on 20/09/2025.
//

#include "test_moves_deck_widget.h"

#include <QMainWindow>

#include "components/move_card.h"


void TestMovesDeckWidget::initTestCase() {
    m_window = new QMainWindow();
    m_window->setGeometry(300, 300, 300, 500);
    m_move_deck = new View::Features::Repertoire::MovesDeck(m_window);
    m_move_deck->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_window->setCentralWidget(m_move_deck);
    m_window->show();
    QVERIFY(QTest::qWaitForWindowExposed(m_window, 5000));
}

void TestMovesDeckWidget::cleanupTestCase() {
    delete m_move_deck;
    delete m_window;
}

void TestMovesDeckWidget::init() {
}

void TestMovesDeckWidget::cleanup() {
    m_move_deck->show();
    QTest::qWait(1000);
}

void TestMovesDeckWidget::testEmptyDeck() {
}

void TestMovesDeckWidget::testSettingCard() {
    m_cards.clear();
    m_cards.append(createTestMoveData({"e2e4"}));
    m_move_deck->setMoves(m_cards);
}

void TestMovesDeckWidget::testSettingSomeCards() {
    m_cards.clear();
    m_cards.append(createTestMoveData({"e2e4"}));
    m_cards.append(createTestMoveData({"f2f4"}));
    m_cards.append(createTestMoveData({"a2a4"}));
    m_move_deck->setMoves(m_cards);
}

void TestMovesDeckWidget::testSettingManyCards() {
    m_cards.clear();
    for (int i = 0; i < 100; i++) {
        m_cards.append(createTestMoveData({"e2e4"}));
    }
    m_move_deck->setMoves(m_cards);
}

void TestMovesDeckWidget::testClearingCards() {
    m_move_deck->setMoves({});
}

void TestMovesDeckWidget::testEmittingMove() {
    QList<Domain::Types::MoveData> cards;
    Domain::Types::UCIMove card1_move{"a2a4"};
    cards.append(createTestMoveData(card1_move));
    cards.append(createTestMoveData({"b2b4"}));
    cards.append(createTestMoveData({"c2c4"}));
    m_move_deck->setMoves(cards);
    QSignalSpy spy(m_move_deck, SIGNAL(moveClicked(Domain::Types::UCIMove)));
    QTest::mouseClick(m_move_deck->getMoveCard(), Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QVERIFY(spy.takeFirst().at(0).value<Domain::Types::UCIMove>() == card1_move);
}

Domain::Types::MoveData TestMovesDeckWidget::createTestMoveData(const Domain::Types::UCIMove &move,
                                                                const Domain::Types::PositionStats &stats) {
    return Domain::Types::MoveData(move, stats);
}

QTEST_MAIN(TestMovesDeckWidget)
#include "test_moves_deck_widget.moc"
