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

#include "board_graphics_scene.h"

namespace View::Features::Board {
    class BoardGraphicsView: public QGraphicsView {
        Q_OBJECT
    public:
        explicit BoardGraphicsView(BoardGraphicsScene* scene, QWidget *parent = nullptr): QGraphicsView(parent) {
            setScene(scene);
            fitInView(sceneRect(), Qt::KeepAspectRatio);
            setRenderHint(QPainter::Antialiasing);
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
        void resizeEvent(QResizeEvent *event) override {
            m_size = std::min(event->size().width(), event->size().height());
            // setFixedSize(m_size, m_size);
            // scene()->setSceneRect(rect());
            fitInView(sceneRect(), Qt::KeepAspectRatio);
            static_cast<BoardGraphicsScene*>(scene())->setSquareSize(m_size / 8);
            QGraphicsView::resizeEvent(event);
        }
    private:
        int m_size;
    };
}



#endif //CHESSREPO_BOARD_GRAPHICS_VIEW_H