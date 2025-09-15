int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Initialize Qt application

    // MainWindow window;             // Create MainWindow object
    // window.show(); // Display window
    application::Application mainApp;
    mainApp.start();

    return app.exec();             // Run the application event loop

}
