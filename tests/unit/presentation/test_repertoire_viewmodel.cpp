//
// Created by Lecka on 21/09/2025.
//

#include "test_repertoire_viewmodel.h"

#include "../../test_utils.h"
#include "domain/types/collections.h"


namespace Test {
    void TestRepertoireViewmodel::initTestCase() {
        m_rep_viewmodel = new Presentation::Features::Repertoire::RepertoireViewModel(this);
    }

    void TestRepertoireViewmodel::cleanupTestCase() {
        delete m_rep_viewmodel;
    }

    void TestRepertoireViewmodel::init() {

    }

    void TestRepertoireViewmodel::cleanup() {
        m_rep_viewmodel->setFEN(Domain::Types::FEN::startingPosition());
    }

    void TestRepertoireViewmodel::testSetEmptyRepertoire() {
        QSignalSpy spy(m_rep_viewmodel, SIGNAL(moveListChanged(QList<Domain::Types::MoveData>)));
        m_rep_viewmodel->setRepertoire({});
        QCOMPARE(spy.count(), 1);
        auto moves = spy.takeFirst().at(0).value<QList<Domain::Types::MoveData>>();
        QCOMPARE(moves.size(), 0);
    }

    void TestRepertoireViewmodel::testSetAndGetRepertoire() {
        const Domain::Types::Repertoire::RepertoireData repertoire = Utils::createTestRepertoire();
        m_rep_viewmodel->setRepertoire(repertoire);
        QCOMPARE(m_rep_viewmodel->getRepertoire(), repertoire);
    }

    void TestRepertoireViewmodel::testAddMove() {
        QSignalSpy spy(m_rep_viewmodel, SIGNAL(moveListChanged(QList<Domain::Types::MoveData>)));
        const Domain::Types::MoveData moveData{{"d2d4"}, {5, 3, 1, 1}};
        m_rep_viewmodel->addMove(moveData);
        QCOMPARE(spy.count(), 1);
        spy.pop_front();
        m_rep_viewmodel->setFEN(Domain::Types::FEN::startingPosition());
        QCOMPARE(spy.count(), 1);
        auto moves = spy.takeFirst().at(0).value<QList<Domain::Types::MoveData>>();
        QVERIFY2(moves.contains<Domain::Types::MoveData>(moveData), "Added Move not found in emitted move list");
    }

    void TestRepertoireViewmodel::testRemoveMove() {
        QSignalSpy spy(m_rep_viewmodel, SIGNAL(moveListChanged(QList<Domain::Types::MoveData>)));
        const Domain::Types::MoveData moveData{{"e2e4"}, {10, 4, 2, 4}};
        m_rep_viewmodel->removeMove(moveData);
        QCOMPARE(spy.count(), 1);
        spy.pop_front();
        m_rep_viewmodel->setFEN(Domain::Types::FEN::startingPosition());
        QCOMPARE(spy.count(), 1);
        auto moves = spy.takeFirst().at(0).value<QList<Domain::Types::MoveData>>();
        QVERIFY2(!moves.contains<Domain::Types::MoveData>(moveData), "Removed Move still found in emitted move list");
    }
}

QTEST_MAIN(Test::TestRepertoireViewmodel)
#include "test_repertoire_viewmodel.moc"
