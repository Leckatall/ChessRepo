//
// Created by Lecka on 24/09/2025.
//

#ifndef CHESSREPO_TEST_REPERTOIRE_SELECTION_VIEWMODEL_H
#define CHESSREPO_TEST_REPERTOIRE_SELECTION_VIEWMODEL_H

#include <QtTest/QtTest>
#include <qtemporarydir.h>

#include "persistence/repertoire_persistence.h"
#include "viewmodels/repertoire_selection_viewmodel.h"
#include "../../test_utils.h"

namespace Test {
    class TestRepertoireSelectionViewmodel : public QObject {
        Q_OBJECT

    private slots:
        void initTestCase();

        void cleanupTestCase();

        // void init();
        //
        // void cleanup();

        void testRepertoireListLoading();
        void testRepertoireSelectionUpdates();
        // void testRepertoireSavePropogation(); ???
        //void testRepertoireDeletion(); TODO
        void testNewRepertoireCreation();
        void testEditRepertoire();

    private:
        Domain::Types::Repertoire::RepertoireData testRepertoireData;
        QTemporaryDir *temp_dir;
        Infrastructure::Features::Repertoire::RepertoirePersistence* m_repertoirePersistence;
        Infrastructure::Features::Repertoire::RepertoireService *m_repertoireService;
        Presentation::Features::Persistence::RepertoireSelectionViewmodel* m_viewmodel;
    };
}


#endif //CHESSREPO_TEST_REPERTOIRE_SELECTION_VIEWMODEL_H
