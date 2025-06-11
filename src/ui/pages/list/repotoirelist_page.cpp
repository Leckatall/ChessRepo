//
// Created by Lecka on 11/06/2025.
//

#include "repotoirelist_page.h"

#include "repocard.h"


RepertoireListPage::RepertoireListPage(QWidget *parent)
    : QWidget(parent),
      m_container(new QWidget(this)),
      m_layout(m_container),
      m_scrollArea(m_container) {
    // Important: Allow container to grow/shrink with content
    m_container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    // m_layout->setAlignment(Qt::AlignTop);
    m_scrollArea.setWidget(m_container);
    m_scrollArea.setWidgetResizable(true);
}

void RepertoireListPage::showRepertoireList(QStringList reps) const {
    const auto scroll_layout = m_scrollArea.layout();
    for (const auto& rep: reps) {
        scroll_layout->addWidget(new RepoCard(rep));
    }
}
