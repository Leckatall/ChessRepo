//
// Created by Lecka on 07/03/2025.
//

#ifndef SQUAREDELEGATE_H
#define SQUAREDELEGATE_H

#include <iostream>
#include <QStyledItemDelegate>
#include <QHash>
#include <QFontDatabase>
#include <QDebug>

inline QHash<QString, QString> STR_TO_UNICODE_PIECE = {
    // White Pieces Lookup
    {"P", "♙"},
    {"N", "♘"},
    {"B", "♗"},
    {"R", "♖"},
    {"Q", "♕"},
    {"K", "♔"},
    // Black Pieces Lookup
    {"p", "♟"},
    {"n", "♞"},
    {"b", "♝"},
    {"r", "♜"},
    {"q", "♛"},
    {"k", "♚"},
    // No Piece
    {".", " "}
};

class SquareDelegate : public QStyledItemDelegate {
public:
    explicit SquareDelegate(QObject *parent = nullptr): QStyledItemDelegate(parent) {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


private:
QString piece_font = "Consolas";
    QColor light_square_color = QColor(100, 100, 100, 100);
    QColor dark_square_color = QColor(0, 0, 0, 100);
};


#endif //SQUAREDELEGATE_H
