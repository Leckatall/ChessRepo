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

#include "ChessCanvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      central_widget(new QWidget(this)),
      status_bar(new QStatusBar(this)),
      button(new QPushButton(central_widget)),
      chessCanvas(new CanvasBoard()) {
    // Set central widget
    setCentralWidget(central_widget);

    // Create status bar
    setStatusBar(status_bar);

    this->initUI();

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


    connect(button, &QPushButton::clicked, chessCanvas, &CanvasBoard::load_FEN);
    initLayout(new QGridLayout());
}

void MainWindow::initLayout(QLayout *layout) {
    chessCanvas->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    layout->addWidget(chessCanvas);
    layout->addWidget(button);
    central_widget->setLayout(layout);
}
