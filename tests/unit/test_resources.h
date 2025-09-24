//
// Created by Lecka on 23/09/2025.
//

#ifndef CHESSREPO_TEST_RESOURCES_H
#define CHESSREPO_TEST_RESOURCES_H

#include <QSvgRenderer>
#include <QtTest/QtTest>

namespace Test {
    class TestResources: public QObject {
        Q_OBJECT
    private slots:
        void listResources();
        void testResourceExists();

    private:
        // QMainWindow m_window;
        // QSvgRenderer m_renderer;
        // QGraphicsWidget *m_graphicsWidget;
    };
}



#endif //CHESSREPO_TEST_RESOURCES_H