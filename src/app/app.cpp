//
// Created by Lecka on 18/09/2025.
//

#include "app.h"

#include "controllers/explorer_controller.h"

namespace Application {
    App::App() : QObject(nullptr),
                 m_lichessApi(this),
                 m_window(new QMainWindow()),
                 m_container(new QFrame()),
                 m_explorerVM(m_lichessApi),
                 m_board_controller(new chessboard::Controller(this)),
                 m_explorerView(new explorer::View(m_container)) {
        m_window->setWindowTitle("ChessRepo");
        m_window->setGeometry(0, 0, 1200, 800);
        m_window->setCentralWidget(m_container);
        m_explorerView->setTblModel(m_explorerVM.tableModel());
        m_explorerView->initTblUi();
        initLayout();
        initConnections();
    }

    void App::initLayout() const {
        const auto layout = new QGridLayout();
        layout->addWidget(m_board_controller->view(), 0, 0);
        layout->addWidget(m_explorerView, 0, 1);
        m_container->setLayout(layout);
    }

    void App::start() const {
        m_window->show();
    }

    void App::initConnections() {
        connect(m_board_controller, &chessboard::Controller::boardChanged,
                &m_explorerVM, &Presentation::Features::Explorer::ExplorerViewModel::setFen);
        connect(m_explorerView, &explorer::View::moveIndexClicked,
                &m_explorerVM, &Presentation::Features::Explorer::ExplorerViewModel::indexClicked);
        connect(&m_explorerVM, &Presentation::Features::Explorer::ExplorerViewModel::moveClicked,
                m_board_controller, &chessboard::Controller::makeUciMove);
    }
}
