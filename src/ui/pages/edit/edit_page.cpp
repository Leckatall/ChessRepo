//
// Created by Lecka on 13/06/2025.
//

#include "edit_page.h"

#include <utility>
#include <models/datatypes.h>

EditPage::EditPage(chessboard::View *board, explorer::View *explorer, QWidget *parent)
    : QWidget(parent),
      m_board(board),
      m_explorer(explorer),
      m_side_panel(new QFrame(this)),
      m_moves_deck(new MovesDeck(this)),
      m_rep_name_edit(new QLineEdit(this)),
      m_comment_edit(new QTextEdit(m_side_panel)),
      m_delete_line_btn(new QPushButton("Delete Line", m_side_panel)),
      m_save_line_btn(new QPushButton("Save Line", m_side_panel)),
      m_back_btn(new QPushButton("Back to Repertoires", this)) {
    initLayout();
    initConnections();
}

void EditPage::initLayout() {
    auto *side_panel_layout = new QGridLayout();
    side_panel_layout->addWidget(m_comment_edit, 0, 0);
    side_panel_layout->addWidget(m_moves_deck, 1, 0);
    side_panel_layout->addWidget(m_explorer, 2, 0);
    side_panel_layout->addWidget(m_save_line_btn, 3, 0);
    side_panel_layout->addWidget(m_delete_line_btn, 3, 1);
    m_side_panel->setLayout(side_panel_layout);

    auto *layout = new QGridLayout();
    layout->addWidget(m_back_btn, 0, 0);
    layout->addWidget(m_rep_name_edit, 0, 1);
    layout->addWidget(m_board, 1, 0);
    layout->addWidget(m_side_panel, 1, 1);
    setLayout(layout);
}

void EditPage::initConnections() {
    connect(m_back_btn, &QPushButton::clicked,
            this, [this] { emit routeToListRequested(); });
    // connect(m_explorer, &explorer::View::moveIndexClicked,
    //         this, [this](const Models::UCIMove &uci) { emit uciMoveRequest(uci); });
}


void EditPage::set_repertoire(const Models::Repertoire &repertoire) const {
    m_rep_name_edit->setText(repertoire.name);
}

void EditPage::updateExplorer() {
}
