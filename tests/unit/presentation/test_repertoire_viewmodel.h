//
// Created by Lecka on 21/09/2025.
//

#ifndef CHESSREPO_TEST_REPERTOIRE_VIEWMODEL_H
#define CHESSREPO_TEST_REPERTOIRE_VIEWMODEL_H

#include <QtTest/QtTest>

#include "viewmodels/repertoire_viewmodel.h"

namespace Test {
    class TestRepertoireViewmodel : public QObject {
        Q_OBJECT
    private slots:
        void initTestCase();        // Runs once before all tests
        void cleanupTestCase();     // Runs once after all tests
        void init();                // Runs before each test
        void cleanup();             // Runs after each test

        void testSetEmptyRepertoire();
        void testSetAndGetRepertoire();
        void testAddMove();
        void testRemoveMove();
        //void testEmitSaveRepertoire(); // Maybe?? Might Handle it in the QMenu
        // void testDisplayMoves();
        // TODO void testMoveClicked();

    private:

        Presentation::Features::Repertoire::RepertoireViewModel* m_rep_viewmodel;
    };
}



#endif //CHESSREPO_TEST_REPERTOIRE_VIEWMODEL_H