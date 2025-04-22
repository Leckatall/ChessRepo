//
// Created by Lecka on 03/03/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>

#include "controllers/boardcontroller.h"
#include "controllers/explorercontroller.h"
#include "controllers/openingcontroller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT // MOC requires this macro for signals and slots

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void initUI();
    void initLayout();
    void initConnections();

    // Private members
    QWidget *central_widget;
    QStatusBar *status_bar;

    BoardController board;
    ExplorerController explorer;
    OpeningController repos;
    QPushButton *button{};
    QPushButton *PracticeRepoBtn{};
    QPushButton *BuildRepoBtn{};

};

#endif
