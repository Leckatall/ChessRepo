//
// Created by Lecka on 11/06/2025.
//

#include "list_page.h"

#include "repocard.h"


ListPage::ListPage(QWidget *parent)
    : QWidget(parent),
      m_scrollArea(new QScrollArea(this)),
      m_scroll_widget(new QWidget),
      m_scroll_layout(new QVBoxLayout(m_scroll_widget)),
      m_create_rep_btn(new QPushButton(this)) {
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_scroll_widget);

    m_scroll_layout->setAlignment(Qt::AlignTop);
    m_scroll_layout->setSpacing(8);

    m_create_rep_btn->setText("Create Repertoire");
    initLayout();
    initConnections();
}

void ListPage::initLayout() {
    const auto layout = new QVBoxLayout();
    //layout->setContentsMargins(0, 0, 0, 0);
    m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_scrollArea);
    layout->addWidget(m_create_rep_btn);
    setLayout(layout);
}

void ListPage::initConnections() {
    connect(m_create_rep_btn, &QPushButton::clicked, this, [this] { emit createRequested(); });
}


void ListPage::updateRepertoireList(const QStringList &reps) {
    while (const QLayoutItem *item = m_scroll_layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    for (const auto &rep: reps) {
        auto *rep_card = new RepoCard(rep, m_scroll_widget);
        connect(rep_card, &RepoCard::studyClicked,
                this, [this](const QString &rep_name) { emit studyRequested(rep_name); });
        connect(rep_card, &RepoCard::editClicked,
                this, [this](const QString &rep_name) { emit editRequested(rep_name); });
        connect(rep_card, &RepoCard::deleteClicked,
                this, [this](const QString &rep_name) { emit deleteRequested(rep_name); });
        m_scroll_layout->addWidget(rep_card);
    }
}
