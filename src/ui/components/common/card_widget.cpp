//
// Created by Lecka on 15/06/2025.
//

#include "card_widget.h"

#include <QMouseEvent>

#include <utility>

namespace common {
    CardWidget::CardWidget(const QString &title, QWidget *parent)
        : QFrame(parent),
          m_title_lbl(new QLabel(title, this)),
          m_content_layout(new QGridLayout()) {
        initStyle();
        auto *main_layout = new QVBoxLayout(this);
        auto *content_conatiner = new QFrame(this);
        content_conatiner->setStyleSheet("QFrame { border-top: 1px solid gray; }");
        content_conatiner->setLayout(m_content_layout);
        m_content_layout->setContentsMargins(10, 10, 10, 10);

        m_content_layout->setSpacing(8);

        main_layout->setContentsMargins(0, 0, 0, 0);
        main_layout->addWidget(m_title_lbl, 0, Qt::AlignCenter);
        main_layout->addWidget(content_conatiner);
        setLayout(main_layout);
    }

    void CardWidget::mousePressEvent(QMouseEvent *event) {
        QFrame::mousePressEvent(event);
        if (event->button() == Qt::LeftButton) {
            emit clicked();
        }
    }

    void CardWidget::initStyle() {
        setFrameStyle(StyledPanel | Raised);
        setStyleSheet(
            "CardWidget {"
            "  background-color: #333333;"
            "  border-radius: 8px;"
            "  border: 1px solid #e0e0e0;"
            "}"
            "CardWidget:hover {"
            "border: 2px solid #c0c0c0;"
            "  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);"
            "}");
    }
}
