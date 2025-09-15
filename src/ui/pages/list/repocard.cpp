//
// Created by Lecka on 11/06/2025.
//

#include "repocard.h"

#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <utility>


RepoCard::RepoCard(QString repotoire_name, QWidget *parent)
    : CardWidget(repotoire_name, parent),
      m_rep(std::move(repotoire_name)) {
    m_title_lbl->setStyleSheet("QLabel { color: white; font-size: 32px; font-weight: bold;}");

    auto study_btn = new QPushButton(tr("Study"), this);
    auto edit_btn = new QPushButton(tr("Edit"), this);
    auto delete_btn = new QPushButton(tr("Delete"), this);

    connect(study_btn, &QPushButton::clicked, this, [this] {emit studyClicked(m_rep);});
    connect(edit_btn, &QPushButton::clicked, this, [this] {emit editClicked(m_rep);});
    connect(delete_btn, &QPushButton::clicked, this, [this] {emit deleteClicked(m_rep);});

    m_content_layout->addWidget(study_btn, 0, 0);
    m_content_layout->addWidget(edit_btn, 0, 1);
    m_content_layout->addWidget(delete_btn, 0, 2);
}
