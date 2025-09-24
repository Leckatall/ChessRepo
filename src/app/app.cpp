//
// Created by Lecka on 18/09/2025.
//

#include "app.h"
#include <QStatusBar>

#include "components/mainwindow/menu_bar.h"

namespace Application {
    App::App() : QObject(nullptr),
                 m_lichessApi(this),
                 m_repertoirePersistence(this),
                 m_window(new QMainWindow()),
                 m_container(new QFrame()),
                 m_explorerVM(m_lichessApi, m_repertoirePersistence),
                 m_repertoireVM(m_repertoire,this),
                 m_board(Domain::Features::Chess::Board()),
                 m_boardVM(m_board, this),
                 m_explorerView(new View::Features::Explorer::ExplorerTable(&m_explorerVM, m_container)),
                 m_repertoireManagerWidget(new View::Features::Repertoire::RepertoireManagerWidget(
                     &m_repertoireVM, m_container)),
                 m_boardTable(new View::Features::Board::ChessboardTable(&m_boardVM, m_container)) {
        m_window->setWindowTitle("ChessRepo");
        m_window->setGeometry(0, 0, 1200, 800);
        m_window->setCentralWidget(m_container);
        m_window->setMenuBar(new View::Features::MainWindow::WindowMenuBar());
        setStatusBarMessage();
        initLayout();
        initConnections();
    }

    void App::initLayout() const {
        // ReSharper disable once CppDFAMemoryLeak
        const auto layout = new QGridLayout(m_container);
        m_boardTable->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        layout->addWidget(m_boardTable, 0, 0, 2, 1);
        m_repertoireManagerWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        layout->addWidget(m_repertoireManagerWidget, 0, 1);
        m_explorerView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        layout->addWidget(m_explorerView, 1, 1);
        layout->setColumnStretch(0, 2);
        layout->setColumnStretch(1, 1);
        m_container->setLayout(layout);
    }

    void App::start() const {
        m_window->show();
    }

    void App::initConnections() {
        connect(&m_boardVM, &Presentation::Features::Board::BoardTableViewModel::boardChanged,
                &m_explorerVM, &Presentation::Features::Explorer::ExplorerViewModel::setFen);
        connect(&m_boardVM, &Presentation::Features::Board::BoardTableViewModel::boardChanged,
                &m_repertoireVM, &Presentation::Features::Repertoire::RepertoireViewModel::setFen);
        connect(&m_explorerVM, &Presentation::Features::Explorer::ExplorerViewModel::moveClicked,
                &m_boardVM, &Presentation::Features::Board::BoardTableViewModel::makeUciMove);
        connect(&m_repertoireVM, &Presentation::Features::Repertoire::RepertoireViewModel::moveClicked,
                &m_boardVM, &Presentation::Features::Board::BoardTableViewModel::makeUciMove);
        connect(&m_repertoireVM, &Presentation::Features::Repertoire::RepertoireViewModel::repertoireChanged,
                this, &App::setStatusBarMessage);
    }

    void App::setStatusBarMessage() const {
        m_window->statusBar()->showMessage(("Loaded Repertoire: " + m_repertoire.header.name).data());
    }
}
