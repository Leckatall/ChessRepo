
#include "explorer_view.h"
#include "explorer_tblmodel.h"
#include "explorer_tblview.h"

namespace explorer {

View::View(QWidget * parent)
        : QWidget(parent),
          m_tblView(new TblView(this)),
          m_current_pos_label(new QLabel("Placeholder", this)) {

        m_current_pos_label->setStyleSheet("QLabel { color: white; font-weight: bold; }");

        auto *layout = new QVBoxLayout();

        layout->addWidget(m_tblView);
        layout->addWidget(m_current_pos_label);
        setLayout(layout);
        initConnections();
}

// SIGNAL 0

void View::moveIndexClicked(const QModelIndex & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

void View::updatePositionLabel() const {

        m_current_pos_label->setText(position_data_str);
}

void View::initConnections() {

        connect(m_tblView, &QTableView::clicked,
                this, [this](const QModelIndex &proxy_index) { emit moveIndexClicked(proxy_index); });
}


} // namespace explorer
