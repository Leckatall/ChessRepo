
#include "openingcontroller.h"
#include "chess_primitives.h"

// TODO: Add lines to currently selected openers
// TODO: Modal popup if there are unsaved changes
// TODO: Display info within selected repo well
// TODO: responses for fen
// TODO: L8r add repo evaluator (coverage, strength, soundness)
OpeningController::OpeningController(QWidget * parent)
    : QObject(parent),
      m_container(new QFrame(parent)),
      m_layout(m_container),
      m_opener_select(m_container),
      m_load_opener_btn("Load Opener", m_container),
      m_save_opener_btn("Save Opener", m_container),
      m_add_line_btn("Add Line", m_container),
      m_repo_service(this),
      m_openers(getOpeners() << m_add_opener_selection) {

    initUI();
    initConnections();
}

QWidget OpeningController::view() const {

    return m_container;
}

QList<Models::UCIMove> OpeningController::responses_for_pos() {

    return m_current_repo.positions[pos].responses.keys();
}

void OpeningController::annotateForPosition() {

}

bool OpeningController::createRepo() {

    if (const auto modal = new CreateRepoModal(m_container); modal->exec() == QDialog::Accepted) {
        m_current_repo = modal->getRepertoire();
        saveRepo();
        return true;
    }
    return false;
}

// SIGNAL 0

void OpeningController::boardChanged(const QString & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void OpeningController::openerChaned() {

    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

void OpeningController::saveRepo() {

    m_repo_service.saveRepertoire(m_current_repo);
}

QList<QString> OpeningController::getOpeners()
{

    return {"Whatever"};
}

void OpeningController::initUI() {

    m_container->setFrameStyle(QFrame::Box);

    m_opener_select.setPlaceholderText("No repo selected");
    update_combo_box();
    m_opener_select.setCurrentIndex(-1);

    m_layout.addWidget(&m_opener_select, 0, 0, 1, 2);
    m_layout.addWidget(&m_load_opener_btn, 0, 2);
    m_layout.addWidget(&m_save_opener_btn, 1, 0);
    m_layout.addWidget(&m_add_line_btn, 1, 1);
    m_container->setLayout(&m_layout);
}

void OpeningController::initConnections() {

    connect(&m_opener_select, &QComboBox::currentIndexChanged,
            this, selectedOpenerChanged);
}

void OpeningController::update_combo_box() {

    const QSignalBlocker blocker(m_opener_select);

    m_opener_select.clear();
    m_opener_select.addItems(m_openers);

    // Restore selection
    if (const int index = m_opener_select.findText(m_current_repo.name); index >= 0) {
        m_opener_select.setCurrentIndex(index);
    }
}

