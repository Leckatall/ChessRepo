//
// Created by Lecka on 06/04/2025.
//

#include "arrowoverlay.h"

#include <QPainter>
#include <QPainterPath>

#include "../../../presentation/models/chessboard/board_proxytblmodel.h"

// void ArrowOverlay::add_arrow(const Arrow &arrow) {
//     m_arrows.append(arrow);
//     update();
// }
//
// void ArrowOverlay::remove_arrow(const Arrow &arrow) {
//     m_arrows.removeAll(arrow);
//     update();
// }
//
// void ArrowOverlay::clear_arrows() {
//     m_arrows.clear();
//     update();
// }
//
// void ArrowOverlay::paintEvent(QPaintEvent *event) {
//     Q_UNUSED(event);
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);
//
//     for (const Arrow &arrow: m_arrows) {
//         draw_arrow(&painter, arrow);
//     }
// }
//
// void ArrowOverlay::draw_arrow(QPainter *painter, const Arrow &arrow) const {
//     // Get the center points of the cells
//     const QPoint start = m_table_view->visualRect(m_proxy_model->square_to_index(arrow.from)).center();
//     const QPoint end = m_table_view->visualRect(m_proxy_model->square_to_index(arrow.to)).center();
//
//     if (start.isNull() || end.isNull()) {
//         qDebug() << "Smth was null";
//         return;
//     }
//     // Define paths in unit size (0 to 1 range)
// //     QPainterPath arrowHeadPath;
// //     arrowHeadPath.moveTo(0.75, 0);
// //     arrowHeadPath.lineTo(0.75, 0.75);
// //     arrowHeadPath.lineTo(1.0, 0.75);
// //     arrowHeadPath.lineTo(0.5, 1.0);
// //     arrowHeadPath.lineTo(0.25, 0.75);
// //     arrowHeadPath.lineTo(0.25, 0);
// //     arrowHeadPath.closeSubpath();
// //
// //     QPainterPath arrowTrailPath;
// //     arrowTrailPath.moveTo(0, 0.25);      // Start left of center
// //     arrowTrailPath.lineTo(0, 0.75);       // To right edge
// //     arrowTrailPath.lineTo(1, 0.75);    // Down
// //     arrowTrailPath.lineTo(1, 0.25);   // Back left
// //     arrowTrailPath.closeSubpath();
// //
// //     // Calculate differences
// //     const int dx = arrow.to.column() - arrow.from.column();
// //     const int dy = arrow.to.row() - arrow.from.row();
// //     qDebug() << "dx:" << dx;
// //     qDebug() << "dy:" << dy;
// //
// //     // Create the transformation matrix with proper scaling
// //     // QTransform transform(
// //     //     (dy > 0) ? 1 : (dy < 0) ? -1 : 0,  // m11
// //     //     -dx,                                 // m12
// //     //     (dx > 0) ? 1 : (dx < 0) ? -1 : 0,  // m21
// //     //     dy,                                 // m22
// //     //     start.x(),                         // dx (translation)
// //     //     start.y()                          // dy (translation)
// //     // );
// //
// //     QTransform transform(
// //     0,    -1,  // m11, m12
// //     1,     0,  // m21, m22
// //     start.x(), start.y()
// // );
// //
// //     // Scale by square_width
// //     transform.scale(square_width, square_width);
// //
// //
//      painter->save();
//      painter->setPen(QPen(arrow.color, 5));
//      // painter->setBrush(arrow.color);
// //     // transform.translate(start.x(), start.y());
// //     painter->setTransform(transform);
//     // painter->drawPath(arrowTrailPath);
//     // painter->drawPath(arrowHeadPath);
//     QPainterPath simpleLine;
//     simpleLine.moveTo(start);
//     simpleLine.lineTo(end);
//     painter->drawPath(simpleLine);
//     painter->restore();
//
//     // QPoint corner = abs(start.x() - end.x()) > abs(start.y() - end.y())
//     //                     ? QPoint(end.x(), start.y())
//     //                     : QPoint(start.x(), end.y());
//     //
//     //
//     //
//     // QLineF line1(start, corner);
//     // QLineF line2(corner, end);
//     //
//     // QPointF perpendicular1 = line1.normalVector().unitVector().p2() - line1.p1();
//     // QPointF perpendicular2 = line2.normalVector().unitVector().p2() - line2.p1();
//     //
//     // // Add the main arrow body
//     // path.moveTo(start - (perpendicular1 * thickness / 2));
//     // path.lineTo(corner - ((perpendicular1 + perpendicular2) * thickness / 2));
//     // path.lineTo(end - (perpendicular2 * thickness / 2) - (perpendicular1 * headSize));
//     // path.lineTo(end - (perpendicular2 * headSize) - (perpendicular1 * headSize));
//     // path.lineTo(end); // Arrow tip
//     // path.lineTo(end + (perpendicular2 * headSize) - (perpendicular1 * headSize));
//     // path.lineTo(end + (perpendicular2 * thickness / 2) - (perpendicular1 * headSize));
//     // path.lineTo(corner + ((perpendicular1 + perpendicular2) * thickness / 2));
//     // path.lineTo(start + (perpendicular1 * thickness / 2));
//     // path.closeSubpath();
//     //
//     // // Draw the path
//     // painter->setPen(Qt::NoPen);
//     // painter->setBrush(arrow.color);
//     // painter->drawPath(path);
// }
