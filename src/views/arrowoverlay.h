//
// Created by Lecka on 06/04/2025.
//

#ifndef ARROWOVERLAY_H
#define ARROWOVERLAY_H
#include <QTableView>
#include <QWidget>

#include "boardtblview.h"


class ArrowOverlay : public QWidget {
    Q_OBJECT

public:
    struct Arrow {
        QModelIndex from;
        QModelIndex to;
        QColor color;

        Arrow(const QModelIndex f, const QModelIndex t, const QColor c = QColor(0, 255, 255, 150)): from(f), to(t), color(c) {
        }

        bool operator==(const Arrow &other) const {
            return from == other.from and to == other.to;
        }
    };

    explicit ArrowOverlay(BoardTblView *parent): QWidget(parent), m_table_view(parent) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);

        // Raise overlay above table
        raise();

        // Keep overlay aligned with table
        connect(m_table_view, &BoardTblView::geometryChanged, this, &ArrowOverlay::updateOverlayGeometry);
        updateGeometry();
    }

    void add_arrow(const Arrow &arrow);

    void remove_arrow(const Arrow &arrow);

    void clear_arrows();

public slots:
    void updateOverlayGeometry() { setGeometry(m_table_view->viewport()->rect()); }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void draw_arrow(QPainter *painter, const Arrow &arrow) const;

    BoardTblView *m_table_view;
    QList<Arrow> m_arrows;
};


#endif //ARROWOVERLAY_H
