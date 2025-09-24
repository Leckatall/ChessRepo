//
// Created by Lecka on 22/09/2025.
//

#include "repertoire_manager_widget.h"

namespace View::Features::Repertoire {
    RepertoireManagerWidget::RepertoireManagerWidget(
        Presentation::Features::Repertoire::RepertoireViewModel *view_model, QWidget *parent)
        : QWidget(parent),
          m_viewModel(view_model),
          m_deck(new MovesDeck(this)),
          m_add_line_btn(new QPushButton("Add Line", this)) {
        initLayout();
        initConnections();
    }

    void RepertoireManagerWidget::initLayout() {
        // ReSharper disable once CppDFAMemoryLeak
        const auto layout = new QVBoxLayout(this);
        layout->addWidget(m_deck);
        layout->addWidget(m_add_line_btn);
        setLayout(layout);
    }

    void RepertoireManagerWidget::initConnections() {
        connect(m_viewModel, &Presentation::Features::Repertoire::RepertoireViewModel::moveListChanged,
                m_deck, &MovesDeck::setMoves);
        connect(m_deck, &MovesDeck::moveClicked,
                m_viewModel, &Presentation::Features::Repertoire::RepertoireViewModel::addNextMove);
        // connect(m_add_line_btn, &QPushButton::clicked,)
    }
}
