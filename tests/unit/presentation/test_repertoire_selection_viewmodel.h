//
// Created by Lecka on 24/09/2025.
//

#ifndef CHESSREPO_TEST_REPERTOIRE_SELECTION_VIEWMODEL_H
#define CHESSREPO_TEST_REPERTOIRE_SELECTION_VIEWMODEL_H

#include <QtTest/QtTest>

#include "persistence/repertoire_persistence.h"
#include "viewmodels/repertoire_selection_viewmodel.h"

namespace Test {
    class TestRepertoireSelectionViewmodel : public QObject {
        Q_OBJECT

    private slots:
        void initTestCase();

        void cleanupTestCase();

        void init();

        void cleanup();


        void testRepertoireListLoading();
        void testRepertoireSelectionUpdates();
        void testRepertoireSavePropogation();
        void testRepertoireDeletion();
        void testNewRepertoireCreation();
        void testEditRepertoire();

    private:
        Infrastructure::Features::Repertoire::RepertoirePersistence m_repertoirePersistence;
        Presentation::Features::Persistence::RepertoireSelectionViewmodel m_viewmodel;
    };
}


#endif //CHESSREPO_TEST_REPERTOIRE_SELECTION_VIEWMODEL_H
