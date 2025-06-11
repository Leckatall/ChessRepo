//
// Created by Lecka on 11/06/2025.
//

#include "repocard.h"

#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <utility>


RepoCard::RepoCard(QString repotoire_name, QWidget *parent)
    : QWidget(parent),
      m_rep(std::move(repotoire_name)) {
    auto layout = new QHBoxLayout(this);

    auto nameLabel = new QLabel(repotoire_name, this);
    auto studyButton = new QPushButton(tr("Study"), this);
    auto editButton = new QPushButton(tr("Edit"), this);
    auto deleteButton = new QPushButton(tr("Delete"), this);

    layout->addWidget(nameLabel, 1);
    layout->addWidget(studyButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
}
