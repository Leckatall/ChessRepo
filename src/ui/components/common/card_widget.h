//
// Created by Lecka on 15/06/2025.
//

#ifndef CARD_WIDGET_H
#define CARD_WIDGET_H
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace common {
    class CardWidget : public QFrame {
        Q_OBJECT

    public:
        explicit CardWidget(const QString& title = "", QWidget *parent = nullptr);

    signals:
        void clicked();

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        QLabel *m_title_lbl;
        QGridLayout *m_content_layout;

    private:
        void initStyle();
    };
} // common

#endif //CARD_WIDGET_H
