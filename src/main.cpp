//
// Created by Lecka on 28/02/2025.
//

#include <iostream>
#include <QApplication>
#include "Mainwindow.h"
#include "chess.hpp"

using namespace chess;

int main(int argc, char *argv[]) {
    Board board = Board();
    std::cout << board;
    QApplication app(argc, argv);  // Initialize Qt application

    MainWindow window;             // Create MainWindow object
    window.show();                 // Display window

    return app.exec();             // Run the application event loop

}
