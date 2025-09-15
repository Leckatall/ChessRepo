
#include "repertoire_view.h"
#include "move.h"
#include "list_widget.h"

namespace repertoire_viewer {

View::View(QWidget * parent)
        : QWidget(parent),
          m_moves_widget(new common::WidgetList(this)) {

        const auto layout = new QVBoxLayout();
        m_moves_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(m_moves_widget);
        setLayout(layout);
}

void View::updateMovesWidget() {

        m_moves_widget->clear_widgets();
        if (moves.isEmpty()) {
            m_moves_widget->add_widget(new QLabel("No Moves found for this FEN", m_moves_widget));
        }
        for(const auto& move: moves) {
            auto* move_card = new MoveCard(move, m_moves_widget);
            connect(move_card, &common::CardWidget::clicked, this, [this, move]{emit move_clicked(move);});
            m_moves_widget->add_widget(move_card);
        }
}

// SIGNAL 0

void View::move_clicked(Models::Move _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}


} // namespace repertoire_viewer
