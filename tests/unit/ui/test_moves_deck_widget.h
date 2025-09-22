//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_TEST_MOVES_DECK_WIDGET_H
#define CHESSREPO_TEST_MOVES_DECK_WIDGET_H
#include <QMainWindow>
#include <QtTest/QtTest>

#include "components/repertoire/moves_deck.h"
#include "components/repertoire/move_card.h"
#include "types/position/position_stats.h"
#include "types/collections.h"

namespace Test {
    class TestMovesDeckWidget : public QObject {
        Q_OBJECT

    private slots:
        void initTestCase(); // Runs once before all tests
        void cleanupTestCase(); // Runs once after all tests
        void init(); // Runs before each test
        void cleanup(); // Runs after each test

        void testEmptyDeck();

        void testSettingCard();

        void testSettingSomeCards();

        void testSettingManyCards();

        void testClearingCards();

        void testEmittingMove();

    private:
        Domain::Types::MoveData createTestMoveData(const Domain::Types::UCIMove &move,
                                                   const Domain::Types::PositionStats &stats = {3, 1, 1, 1});

        QMainWindow *m_window;
        View::Features::Repertoire::MovesDeck *m_move_deck;
        QList<Domain::Types::MoveData> m_cards;
    };
}


#endif //CHESSREPO_TEST_MOVES_DECK_WIDGET_H
