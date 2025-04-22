//
// Created by Lecka on 03/03/2025.
//


#include "MainWindow.h"

#include <chess.hpp>
#include <iostream>
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <ranges>
#include <QFrame>
#include <QHeaderView>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      central_widget(new QWidget(this)),
      status_bar(new QStatusBar(this)),

      button(new QPushButton(this)),

      board(this),
      explorer(this),
      repos(this) {
    // Set central widget
    setCentralWidget(central_widget);

    // Create status bar
    setStatusBar(status_bar);

    initUI();
    initLayout();
    initConnections();

    // Connect button click to the quit function
    // connect(button, &QPushButton::clicked, this, &QMainWindow::close);
}

void MainWindow::initUI() {
    setWindowTitle("ChessRepo");
    setGeometry(0, 0, 1200, 800);


    // Create file menu and exit action
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    fileMenu->addAction(exitAction);


    status_bar->showMessage("Ready");
    // Create view menu
    QMenu *viewMenu = menuBar()->addMenu("View");

    // connect(button, &QPushButton::clicked, chessCanvas, &CanvasBoard::load_FEN);
}

void MainWindow::initLayout() {
    const auto layout = new QGridLayout();
    // QGridLayout.addWidget(row: int, column: int, rowSpan: int, columnSpan: int, alignment: Qt.Alignment)
    board.view()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    explorer.view()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    layout->addWidget(repos.view(), 0, 1);
    layout->addWidget(board.view(), 1, 0);
    layout->addWidget(explorer.view(), 1, 1, 2, 1);
    // layout->addWidget(button);
    central_widget->setLayout(layout);
}

void MainWindow::initConnections() {
    explorer.exploreFen(board.get_current_fen());
    // Update explorer on board change
    connect(&board, &BoardController::boardChanged,
            &explorer, &ExplorerController::exploreFen);
    // Make move clicked in explorer
    connect(&explorer, &ExplorerController::moveClicked,
            &board, &BoardController::makeUciMove);
}
