//
// Created by Lecka on 03/03/2025.
//


#include "ChessCanvas.h"

#include <chess.hpp>
#include <iostream>
#include <ranges>

CanvasBoard::CanvasBoard(QWidget *parent)
    : QFrame(parent),
      board_size(std::min(this->width(), this->height())),
      square_size(board_size / 8),
      board_layout(new QGridLayout()) {
    this->initUI();
}

void CanvasBoard::initUI() {
    board_layout->setSpacing(0);

    // auto *square = new ChessSquare(1, true, this->square_size);
    // board_layout->addWidget(square);
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto *square = new ChessSquare(((row * 8) + col), ((row + col) % 2 == 0), this->square_size);
            board_layout->addWidget(square, row, col);
        }
    }
    this->setLayout(board_layout);
}

void CanvasBoard::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);

    int l = std::min(this->width(), this->height());
    QPoint center = this->rect().center();
    auto rect = new QRect(0, 0, l, l);
    rect->moveCenter(center);
    this->setGeometry(*rect);
}

void CanvasBoard::load_FEN() {
    std::string FEN = (new chess::Board())->getFen();
    for (auto [square, new_value] : std::views::zip(findChildren<QLabel*>(), FEN)){
        square->setText(new_value);
    }
}

ChessSquare::ChessSquare(int square_id, bool is_white, int square_size)
    : square_id(square_id), is_white(is_white), square_size(square_size) {
    initUI();
}

void ChessSquare::initUI() {
    this->setGeometry(0, 0, square_size, square_size);
    QFont font = this->font();
    font.setPointSizeF(this->square_size * 0.6);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet(DEFAULT_SQUARE_STYLE.arg(is_white ? WHITE_SQUARE : BLACK_SQUARE));
    this->setText(piece);
}
