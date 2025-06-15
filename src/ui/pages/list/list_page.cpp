//
// Created by Lecka on 11/06/2025.
//

#include "list_page.h"

#include "repocard.h"


ListPage::ListPage(QWidget *parent)
    : QWidget(parent),
      m_widget_list(new common::WidgetList(this)),
      m_create_rep_btn(new QPushButton(this)) {
    m_create_rep_btn->setText("Create Repertoire");
    initLayout();
    initConnections();
}

void ListPage::initLayout() {
    const auto layout = new QVBoxLayout();
    //layout->setContentsMargins(0, 0, 0, 0);
    m_widget_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_widget_list);
    layout->addWidget(m_create_rep_btn);
    setLayout(layout);
}

void ListPage::initConnections() {
    connect(m_create_rep_btn, &QPushButton::clicked, this, [this] { emit createRequested(); });
}


void ListPage::updateRepertoireList(const QStringList &reps) {
    m_widget_list->clear_widgets();
    for (const auto &rep: reps) {
        auto *rep_card = new RepoCard(rep, m_widget_list);
        connect(rep_card, &RepoCard::studyClicked,
                this, [this](const QString &rep_name) { emit studyRequested(rep_name); });
        connect(rep_card, &RepoCard::editClicked,
                this, [this](const QString &rep_name) { emit editRequested(rep_name); });
        connect(rep_card, &RepoCard::deleteClicked,
                this, [this](const QString &rep_name) { emit deleteRequested(rep_name); });
        m_widget_list->add_widget(rep_card);
    }
}
