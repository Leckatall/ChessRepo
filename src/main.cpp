//
// Created by Lecka on 28/02/2025.
//

#include <iostream>
#include "chess.hpp"
#include <QApplication>
#include <qurl.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>

#include "controllers/board_controller.h"
//
// #include "controllers/opening_controller.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Create services and controllers
    // OpeningController openingController;
    // ApiService apiService;
    BoardController boardController;

    // Expose to QML context
    // engine.rootContext()->setContextProperty("openingController", &openingController);
    // engine.rootContext()->setContextProperty("apiService", &apiService);
    engine.rootContext()->setContextProperty("boardController", &boardController);
    // Load main QML
    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));

    if (engine.rootObjects().isEmpty()) {
        std::cout << "did not find qml";
        return -1;
    }

    return app.exec();             // Run the application event loop

}

