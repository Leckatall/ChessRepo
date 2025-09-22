//
// Created by Lecka on 20/09/2025.
//

#include "test_repertoire_persistence.h"

#include <iostream>

#include "../test_utils.h"
namespace Test {
    void TestRepertoirePersistence::initTestCase() {
    temp_dir = new QTemporaryDir();
    QVERIFY(temp_dir->isValid());
    persistence = new Infrastructure::Features::Repertoire::RepertoirePersistence(temp_dir->path().toStdString() + "/");
}

void TestRepertoirePersistence::cleanupTestCase() {
    delete persistence;
    delete temp_dir;
}

void TestRepertoirePersistence::init() {
}

void TestRepertoirePersistence::cleanup() {

}

void TestRepertoirePersistence::testSaveAndLoad() {
    // Arrange
    auto originalRepertoire = Test::Utils::createTestRepertoire();

    // Act
    QVERIFY_THROWS_NO_EXCEPTION(persistence->save_repertoire(originalRepertoire));

    auto new_persistence = new Infrastructure::Features::Repertoire::RepertoirePersistence(temp_dir->path().toStdString() + "/");
    auto loadedRepertoire = new_persistence->get_repertoire(originalRepertoire.header.name);

    // Assert
    QCOMPARE(originalRepertoire, loadedRepertoire);
}

void TestRepertoirePersistence::testCaching() {
    // Test that repeated loads use cache
    auto repertoire = Test::Utils::createTestRepertoire();

    persistence->save_repertoire(repertoire);

    // First load
    auto start1 = std::chrono::high_resolution_clock::now();
    auto loaded1 = persistence->get_repertoire(repertoire.header.name);
    auto end1 = std::chrono::high_resolution_clock::now();

    // Second load (should be cached)
    auto start2 = std::chrono::high_resolution_clock::now();
    auto loaded2 = persistence->get_repertoire(repertoire.header.name);
    auto end2 = std::chrono::high_resolution_clock::now();

    // Second load should be faster (assuming caching works)
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

    QVERIFY(duration2 < duration1); // Cached version should be faster
}

void TestRepertoirePersistence::testFileNotFound() {
    QString nonExistentFile = "does_not_exist";

    QVERIFY(persistence->get_repertoire(nonExistentFile.toStdString()) == Domain::Types::Repertoire::RepertoireData{});
}

void TestRepertoirePersistence::testRoundTripPreservation() {
    // Create complex test data
    auto original = Test::Utils::createTestRepertoire();
    // Add complex nested data, optional fields, edge cases...

    // Save and load
    persistence->save_repertoire(original);
    auto loaded = persistence->get_repertoire(original.header.name);

    // Deep comparison - you might want to implement operator== for your types
    QVERIFY(original == loaded);
}

}
QTEST_GUILESS_MAIN(Test::TestRepertoirePersistence)
//#include "test_repertoire_persistence.moc"