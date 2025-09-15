
#include "list_page.h"
#include "list_widget.h"

ListPage::ListPage(QWidget * parent)
    : QWidget(parent),
      m_widget_list(new common::WidgetList(this)),
      m_create_rep_btn(new QPushButton(this)) {

    m_create_rep_btn->setText("Create Repertoire");
    initLayout();
    initConnections();
}

// Methods to update UI state
void ListPage::updateRepertoireList() {

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

// SIGNAL 0

void ListPage::repertoireSelected(int _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void ListPage::createRequested() {

    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2

void ListPage::deleteRequested(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3

void ListPage::editRequested(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4

void ListPage::studyRequested(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
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

