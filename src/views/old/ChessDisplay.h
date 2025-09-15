//
// Created by Lecka on 03/03/2025.
//

#ifndef CHESSCANVAS_H
#define CHESSCANVAS_H

#include <chess.hpp>
#include <QFrame>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QMouseEvent>

#include "ChessBoard.h"

// const std::unordered_map<char, std::string> UNICODE_PIECE_SYMBOLS = {
//     {'R', "♖"}, {'r', "♜"},
//     {'N', "♘"}, {'n', "♞"},
//     {'B', "♗"}, {'b', "♝"},
//     {'Q', "♕"}, {'q', "♛"},
//     {'K', "♔"}, {'k', "♚"},
//     {'P', "♙"}, {'p', "♟"},
//     {'.', ""}
// };
// Stupid language needs me to tell it how to hash the easiest to hash thing in the world...
namespace std {
    template<>
    struct hash<chess::Square> {
        size_t operator()(const chess::Square &s) const noexcept {
            return static_cast<size_t>(s.index()); // Convert to integer index
        }
    };
}

const std::unordered_map<chess::Piece::underlying, std::string> UNICODE_PIECE_SYMBOLS = {
    {chess::Piece::WHITEPAWN, "♙"}, {chess::Piece::WHITEKNIGHT, "♘"},
    {chess::Piece::WHITEBISHOP, "♗"}, {chess::Piece::WHITEROOK, "♖"},
    {chess::Piece::WHITEQUEEN, "♕"}, {chess::Piece::WHITEKING, "♔"},
    {chess::Piece::BLACKPAWN, "♟"}, {chess::Piece::BLACKKNIGHT, "♞"},
    {chess::Piece::BLACKBISHOP, "♝"}, {chess::Piece::BLACKROOK, "♜"},
    {chess::Piece::BLACKQUEEN, "♛"}, {chess::Piece::BLACKKING, "♚"},
    {chess::Piece::NONE, " "}
};

class ChessSquareLbl : public QLabel {
    Q_OBJECT

public:
    ChessSquareLbl(chess::Square square, int square_size);

    void set_piece(chess::Piece new_piece);

    void make_target();
    void select();
    void clear_selection();

    chess::Piece piece = chess::Piece();
    bool target = false;

signals:
    void clicked(chess::Square square);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(square);
        }
    }

private:
    void initUI();

    chess::Square square;
    int square_size;

    const QString DEFAULT_SQUARE_STYLE = QStringLiteral(R"(
            QLabel {
                border: 1px solid black;
                background-color: rgba%1;
            }
            QLabel:hover {
                background-color: rgba(200, 200, 200, 150);
            }
        )");
    const QString WHITE_SQUARE = "(100, 100, 100, 100)";
    const QString BLACK_SQUARE = "(0, 0, 0, 100)";
};

class DisplayBoard : public QFrame {
    Q_OBJECT

public:
    explicit DisplayBoard(QWidget *parent = nullptr);

    void display();

    void make_move(chess::Move move);

    ChessBoard board;
    std::unordered_map<chess::Square, ChessSquareLbl *> label_map;
    chess::Square selected_square = chess::Square(64);
    std::list<chess::Square> targeted_squares;
    chess::Movelist enabled_moves;

private:
    void initUI();

    void resizeEvent(QResizeEvent *event) override;

    int board_size{};
    int square_size{};


private slots:
    void square_clicked(chess::Square square);
};


#endif //CHESSCANVAS_H
