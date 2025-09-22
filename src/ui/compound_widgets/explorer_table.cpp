//
// Created by Lecka on 22/09/2025.
//

#include "explorer_table.h"

#include <qboxlayout.h>

namespace View::Features::Explorer {
    ExplorerTable::ExplorerTable(Presentation::Features::Explorer::ExplorerViewModel *view_model,
                                 QWidget *parent)
        : QWidget(parent),
          m_viewModel(view_model),
          m_tblView(new explorer::TblView(this)),
          m_current_pos_label(new QLabel(this)) {
        m_tblView->setModel(m_viewModel->tableModel());
        m_tblView->initUI();
        initLayout();
        initConnections();
    }

    void ExplorerTable::updatePositionStatsLabel() const {
        m_current_pos_label->setText(m_viewModel->positionSummary());
    }

    void ExplorerTable::initLayout() {
        // ReSharper disable once CppDFAMemoryLeak
        const auto layout = new QVBoxLayout(this);
        layout->addWidget(m_tblView);
        layout->addWidget(m_current_pos_label);
        setLayout(layout);
    }

    void ExplorerTable::initConnections() {
        connect(m_tblView, &explorer::TblView::clicked,
                this, [this](const QModelIndex &index) { emit moveIndexClicked(index); });
        connect(m_viewModel, &Presentation::Features::Explorer::ExplorerViewModel::positionSummaryChanged,
                this, &ExplorerTable::updatePositionStatsLabel);
    }
}
