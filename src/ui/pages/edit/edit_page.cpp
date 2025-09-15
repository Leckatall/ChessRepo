
#include "edit_page.h"
#include "board_view.h"
#include "explorer_view.h"
#include "repertoire_view.h"
#include "chess_primitives.h"
#include "moves_deck.h"

EditPage::EditPage(const EditPage::Components & components, QWidget * parent)
    : QWidget(parent),
      m_side_panel(new QFrame(this)),
      m_rep_name_edit(new QLineEdit(this)),
      m_comment_edit(new QTextEdit(m_side_panel)),
      m_delete_line_btn(new QPushButton("Delete Line", m_side_panel)),
      m_save_line_btn(new QPushButton("Save Line", m_side_panel)),
      m_back_btn(new QPushButton("Back to Repertoires", this)) {

    auto *side_panel_layout = new QGridLayout();
    side_panel_layout->addWidget(m_comment_edit, 0, 0);
    side_panel_layout->addWidget(components.repView, 1, 0);
    side_panel_layout->addWidget(components.explorerView, 2, 0);
    side_panel_layout->addWidget(m_save_line_btn, 3, 0);
    side_panel_layout->addWidget(m_delete_line_btn, 3, 1);
    m_side_panel->setLayout(side_panel_layout);

    auto *layout = new QGridLayout();
    layout->addWidget(m_back_btn, 0, 0);
    layout->addWidget(m_rep_name_edit, 0, 1);
    layout->addWidget(components.boardView, 1, 0);
    layout->addWidget(m_side_panel, 1, 1);
    setLayout(layout);
    initConnections();
}

void EditPage::set_repertoire() const {

    m_rep_name_edit->setText(repertoire.name);
}

// SIGNAL 0

void EditPage::saveRequested() {

    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1

void EditPage::addCurrentLine(QString _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3

void EditPage::moveAdded(const Models::FEN & _t1, const Models::UCIMove & _t2) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4

void EditPage::moveDeleted(const Models::FEN & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5

void EditPage::commentUpdated(const Models::FEN & _t1, const QString & _t2) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6

void EditPage::routeToListRequested() {

    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7

void EditPage::explorerUpdateRequested(const Models::FEN & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

void EditPage::initConnections() {

    connect(m_back_btn, &QPushButton::clicked,
            this, [this] { emit routeToListRequested(); });
    connect(m_save_line_btn, &QPushButton::clicked,
            this, [this] { emit addCurrentLine(); });
}

