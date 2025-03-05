//
// Created by Lecka on 28/02/2025.
//

#include <iostream>
#include "chess.hpp"
#include <QApplication>
#include "MainWindow.h"
#include "Explorer.h"



using namespace chess;

int main(int argc, char *argv[]) {
    auto explore = Explorer();
    explore.getMoves();
    QApplication app(argc, argv);  // Initialize Qt application

    MainWindow window;             // Create MainWindow object
    window.show(); // Display window

    return app.exec();             // Run the application event loop

}
