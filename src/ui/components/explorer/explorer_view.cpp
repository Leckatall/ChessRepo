//
// Created by Lecka on 14/06/2025.
//

#include "explorer_view.h"

#include <qboxlayout.h>

namespace explorer {
    View::View(QWidget *parent)
        : QWidget(parent),
          m_tblView(new TblView(this)),
          m_current_pos_label(new QLabel("Placeholder", this)) {
        m_current_pos_label->setStyleSheet("QLabel { color: white; font-weight: bold; }");

        auto *layout = new QVBoxLayout();

        layout->addWidget(m_tblView);
        layout->addWidget(m_current_pos_label);
        setLayout(layout);
        initConnections();
    }

    void View::initConnections() {
        connect(m_tblView, &QTableView::clicked,
                this, [this](const QModelIndex &proxy_index) { emit moveIndexClicked(proxy_index); });
    }


    void View::updatePositionLabel(const QString &position_data_str) const {
        m_current_pos_label->setText(position_data_str);
    }
}
