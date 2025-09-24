//
// Created by Lecka on 24/09/2025.
//

#ifndef CHESSREPO_MENU_BAR_H
#define CHESSREPO_MENU_BAR_H
#include <QMenuBar>
#include <qtmetamacros.h>

namespace View::Features::MainWindow {
    class WindowMenuBar: public QMenuBar {
        Q_OBJECT
    public:
        explicit WindowMenuBar(QWidget* parent = nullptr) : QMenuBar(parent) {
            QMenu* fileMenu = this->addMenu(tr("&File"));
            QAction* newAction = fileMenu->addAction(tr("&New"));
            QAction* openAction = fileMenu->addAction(tr("&Open"));
            fileMenu->addSeparator();
            QAction* exitAction = fileMenu->addAction(tr("E&xit"));
        }
    };
}

#endif //CHESSREPO_MENU_BAR_H
