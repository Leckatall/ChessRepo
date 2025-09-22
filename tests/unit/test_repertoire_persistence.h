//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_TEST_REPERTOIRE_PERSISTENCE_H
#define CHESSREPO_TEST_REPERTOIRE_PERSISTENCE_H
#include <QtTest/QtTest>
#include <qtemporarydir.h>

#include "persistence/repertoire_persistence.h"
#include "repertoire/repertoire.h"

namespace Test {
    class TestRepertoirePersistence: public QObject {
        Q_OBJECT
        private slots:
        void initTestCase();        // Runs once before all tests
        void cleanupTestCase();     // Runs once after all tests


        void init();                // Runs before each test
        void cleanup();             // Runs after each test

        void testSaveAndLoad();
        void testCaching();
        void testFileNotFound();
        //void testInvalidData();
        void testRoundTripPreservation();

    private:
        Infrastructure::Features::Repertoire::RepertoirePersistence* persistence;
        QTemporaryDir *temp_dir;

    };
}

#endif //CHESSREPO_TEST_REPERTOIRE_PERSISTENCE_H