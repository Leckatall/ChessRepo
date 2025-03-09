//
// Created by Lecka on 03/03/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>

#include "boardtblview.h"
#include "controllers/boardcontroller.h"
#include "models/boardtblmodel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT // MOC requires this macro for signals and slots

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void initUI();

    void initLayout(QLayout *layout);

    // Private members
    QWidget *central_widget;
    QStatusBar *status_bar;

    BoardController board;

    QPushButton *button{};
    QPushButton *PracticeRepoBtn{};
    QPushButton *BuildRepoBtn{};

};

#endif
