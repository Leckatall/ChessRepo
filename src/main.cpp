//
// Created by Lecka on 28/02/2025.
//

#include <QApplication>

#include "app/app.h"
#include "app/application.h"


void declare_metatypes() {
    qRegisterMetaType<Domain::Types::FEN>("FEN");
    qRegisterMetaType<Domain::Types::UCIMove>("UCIMove");
    qRegisterMetaType<Domain::Types::PositionStats>("Domain::Types::PositionStats");
    qRegisterMetaType<Domain::Types::PositionKey>("Domain::Types::PositionKey");
    qRegisterMetaType<Domain::Types::PositionGraph>("Domain::Types::PositionGraph");
}

int main(int argc, char *argv[]) {
    declare_metatypes();
    QApplication app(argc, argv);  // Initialize Qt application

    // MainWindow window;             // Create MainWindow object
    // window.show(); // Display window
    // application::Application mainApp;
    // mainApp.start();
    Application::App v2;
    v2.start();

    return app.exec();             // Run the application event loop
}
