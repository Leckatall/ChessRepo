//
// Created by Lecka on 23/09/2025.
//

#include "test_resources.h"

namespace Test {
    void TestResources::listResources() {
        const QString& path = ":/";
        QDirIterator it(path, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            qDebug() << it.next();
        }
    }
    void TestResources::testResourceExists() {
        QFile file(":/chess/w_king.svg");
        QVERIFY2(file.exists(), "resource file does not exist");
    }
}

QTEST_GUILESS_MAIN(Test::TestResources)