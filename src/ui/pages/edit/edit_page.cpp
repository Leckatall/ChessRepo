//
// Created by Lecka on 13/06/2025.
//

#include "edit_page.h"

#include <utility>
#include <models/datatypes.h>

EditPage::EditPage(const Components &components, QWidget *parent)
    : QWidget(parent),
      m_side_panel(new QFrame(this)),
      m_rep_name_edit(new QLineEdit(this)),
      m_comment_edit(new QTextEdit(m_side_panel)),
      m_delete_line_btn(new QPushButton("Delete Line", m_side_panel)),
      m_save_line_btn(new QPushButton("Save Line", m_side_panel)),
      m_back_btn(new QPushButton("Back to Repertoires", this)) {
    auto *side_panel_layout = new QGridLayout();
    side_panel_layout->addWidget(m_comment_edit, 0, 0);
    side_panel_layout->addWidget(components.repView, 1, 0);
    side_panel_layout->addWidget(components.explorerView, 2, 0);
    side_panel_layout->addWidget(m_save_line_btn, 3, 0);
    side_panel_layout->addWidget(m_delete_line_btn, 3, 1);
    m_side_panel->setLayout(side_panel_layout);

    auto *layout = new QGridLayout();
    layout->addWidget(m_back_btn, 0, 0);
    layout->addWidget(m_rep_name_edit, 0, 1);
    layout->addWidget(components.boardView, 1, 0);
    layout->addWidget(m_side_panel, 1, 1);
    setLayout(layout);
    initConnections();
}

void EditPage::initConnections() {
    connect(m_back_btn, &QPushButton::clicked,
            this, [this] { emit routeToListRequested(); });
    connect(m_save_line_btn, &QPushButton::clicked,
            this, [this] { emit addCurrentLine(); });
}


void EditPage::set_repertoire(const Models::Repertoire &repertoire) const {
    m_rep_name_edit->setText(repertoire.name);
}
