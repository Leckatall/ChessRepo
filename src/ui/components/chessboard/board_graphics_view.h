//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_BOARD_GRAPHICS_VIEW_H
#define CHESSREPO_BOARD_GRAPHICS_VIEW_H
#include <qevent.h>
#include <qobjectdefs.h>
#include <qtmetamacros.h>
#include <QGraphicsView>
#include <QGraphicsScene>

namespace View::Features::Board {
    class BoardGraphicsView: public QGraphicsView {
        Q_OBJECT
    public:
        explicit BoardGraphicsView(QGraphicsScene scene, QWidget *parent = nullptr): QGraphicsView(parent) {
            setScene(&scene);
            setRenderHint(QPainter::Antialiasing);
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
        void resizeEvent(QResizeEvent *event) override {
            m_size = std::min(event->size().width(), event->size().height());
            setFixedSize(m_size, m_size);
            fitInView(sceneRect(), Qt::KeepAspectRatio);
            QGraphicsView::resizeEvent(event);
        }
    private:
        int m_size;
        QGraphicsScene m_scene;
    };
}



#endif //CHESSREPO_BOARD_GRAPHICS_VIEW_H