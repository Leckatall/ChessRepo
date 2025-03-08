//
// Created by Lecka on 28/02/2025.
//

#include <iostream>
#include "chess.hpp"
#include <QApplication>
#include "views/mainwindow.h"



using namespace chess;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Initialize Qt application

    MainWindow window;             // Create MainWindow object
    window.show(); // Display window

    return app.exec();             // Run the application event loop

}
