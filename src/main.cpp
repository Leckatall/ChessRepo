//
// Created by Lecka on 28/02/2025.
//

#include <QApplication>

#include "app/application.h"



using namespace chess;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Initialize Qt application

    // MainWindow window;             // Create MainWindow object
    // window.show(); // Display window
    application::Application mainApp;
    mainApp.start();

    return app.exec();             // Run the application event loop

}
