
#include "repocard.h"

RepoCard::RepoCard(QString repotoire_name, QWidget * parent)
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

// SIGNAL 0

void RepoCard::editClicked(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void RepoCard::studyClicked(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2

void RepoCard::deleteClicked(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

