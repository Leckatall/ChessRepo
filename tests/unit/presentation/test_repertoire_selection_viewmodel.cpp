//
// Created by Lecka on 24/09/2025.
//

#include "test_repertoire_selection_viewmodel.h"


namespace Test {
    void TestRepertoireSelectionViewmodel::initTestCase() {
        testRepertoireData = Utils::createTestRepertoire();
        temp_dir = new QTemporaryDir();
        QVERIFY(temp_dir->isValid());
        m_repertoirePersistence = new Infrastructure::Features::Repertoire::RepertoirePersistence(temp_dir->path().toStdString() + "/");
        m_repertoireService = new Infrastructure::Features::Repertoire::RepertoireService(*m_repertoirePersistence, this);
        m_viewmodel = new Presentation::Features::Persistence::RepertoireSelectionViewmodel(*m_repertoireService, this);
        m_repertoirePersistence->save_repertoire(testRepertoireData, false);
    }

    void TestRepertoireSelectionViewmodel::cleanupTestCase() {
        delete temp_dir;
        delete m_repertoirePersistence;
        delete m_repertoireService;
        delete m_viewmodel;
    }

    void TestRepertoireSelectionViewmodel::testRepertoireListLoading() {
        auto rep_list = m_viewmodel->getRepertoireList();
        QCOMPARE(rep_list.size(), 1);
        QCOMPARE(rep_list.first(), QString::fromStdString(testRepertoireData.header.name));
    }

    void TestRepertoireSelectionViewmodel::testRepertoireSelectionUpdates() {
        m_viewmodel->selectRepertoire(QString::fromStdString(testRepertoireData.header.name));
        auto rep_data = m_viewmodel->getRepertoireData();
        QCOMPARE(rep_data.header.name, testRepertoireData.header.name);
    }

    void TestRepertoireSelectionViewmodel::testNewRepertoireCreation() {
        m_viewmodel->createNewRepertoire(Domain::Types::Repertoire::Header{"New Rep",
            "A new repertoire",
            "Tester",
            true,
            std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now())});
        auto rep_list = m_viewmodel->getRepertoireList();
        QCOMPARE(rep_list.size(), 2);
        QVERIFY(rep_list.contains("New Rep.rep"));
    }

    void TestRepertoireSelectionViewmodel::testEditRepertoire() {
        m_viewmodel->selectRepertoire("New Rep");
        auto rep_data = m_viewmodel->getRepertoireData();
        QCOMPARE(rep_data.header.name, "New Rep");
        Domain::Types::Repertoire::Header new_header = rep_data.header;
        new_header.author = "Edited Author";
        m_viewmodel->editRepertoireHeader(new_header);
        rep_data = m_viewmodel->getRepertoireData();
        QCOMPARE(rep_data.header.author, "Edited Author");
    }
}

QTEST_MAIN(Test::TestRepertoireSelectionViewmodel)
#include "test_repertoire_selection_viewmodel.moc"
