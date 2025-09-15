
#include "board_view.h"
#include "board_tblview.h"

namespace chessboard {

View::View(QWidget * parent)
        : QWidget(parent),
          m_flip_btn(new QPushButton(this)),
          m_undo_btn(new QPushButton(this)),
          m_move_history_lbl(new QLabel(this)),
          m_tblView(new TblView(this)) {

        m_flip_btn->setText("Flip board");
        m_undo_btn->setText("Undo move");
        auto *layout = new QVBoxLayout();

        layout->addWidget(m_tblView);
        layout->addWidget(m_move_history_lbl);
        layout->addWidget(m_flip_btn);
        layout->addWidget(m_undo_btn);
        setLayout(layout);

        initConnections();
}

void View::setHistoryLabel() const {

        m_move_history_lbl->setText(pgn_str);
}

// SIGNAL 0

void View::square_clicked(QModelIndex _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void View::flipRequested() {

    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2

void View::undoMoveRequested() {

    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

void View::initConnections() {

        connect(m_flip_btn, &QPushButton::clicked,
                this, [this] {
                    emit flipRequested();
                });
        connect(m_undo_btn, &QPushButton::clicked,
                this, [this] {
                    emit undoMoveRequested();
                });
        connect(m_tblView, &TblView::squareClicked,
                this, [this](QModelIndex index) {
                    emit square_clicked(index);
                });
}


} // namespace chessboard
