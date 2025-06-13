//
// Created by Lecka on 11/06/2025.
//

#include "repotoirelist_page.h"

#include "repocard.h"


RepertoireListPage::RepertoireListPage(QWidget *parent)
    : QWidget(parent),
      m_container(new QWidget(this)),
      m_scrollArea(new QScrollArea(m_container)),
      m_scroll_widget(new QWidget),
      m_scroll_layout(new QVBoxLayout(m_scroll_widget)) {
    // Important: Allow container to grow/shrink with content
    // m_container->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    //
    // // m_layout->setAlignment(Qt::AlignTop);
    // auto frame = new QFrame(m_scrollArea);
    // auto frameLayout = new QVBoxLayout(frame);
    // frameLayout->setAlignment(Qt::AlignTop);
    // m_scrollArea->setWidget(frame);
    // m_scrollArea->setWidgetResizable(true);
    // m_scrollArea->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    // m_layout.addWidget(m_scrollArea);
    // setLayout(&m_layout);

    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_scroll_widget);

    m_scroll_layout->setAlignment(Qt::AlignTop);
    m_scroll_layout->setSpacing(8);
}

void RepertoireListPage::initLayout() {
    const auto layout = new QVBoxLayout();
    m_scrollArea->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout->addWidget(m_scrollArea);
    setLayout(layout);
}

void RepertoireListPage::updateRepertoireList(const QStringList &reps) {
    while (QLayoutItem* item = m_scroll_layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    for (const auto &rep: reps) {
        auto* rep_card = new RepoCard(rep, m_scroll_widget);
        m_scroll_layout->addWidget(rep_card);
    }
}
