//
// Created by Lecka on 03/03/2025.
//

#ifndef CHESSCANVAS_H
#define CHESSCANVAS_H

#include <QFrame>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QString>

class CanvasBoard : public QFrame {
    Q_OBJECT

public:
    CanvasBoard(QWidget *parent = nullptr);
    void load_FEN();
    // void load_FEN(std::string FEN);
private:
    void initUI();
    void resizeEvent(QResizeEvent *event) override;

    int board_size{};
    int square_size{};
    QGridLayout *board_layout;
};

class ChessSquare : public QLabel {
    Q_OBJECT

public:
    ChessSquare(int square_id, bool is_white, int square_size);

private:
    void initUI();


    // void set_piece();
    //
    // void clear_piece();
    //
    // void select();
    //
    // void deselect();
    //
    // void highlight();

    int square_id;
    bool is_white;
    int square_size;
    QString piece;
    bool highlighted = false;

    const QString DEFAULT_SQUARE_STYLE = QStringLiteral(R"(
            QLabel {
                border: 1px solid black;
                background-color: rgba%1;
            }
            QLabel:hover {
                background-color: rgba(200, 200, 200, 150);
            }
        )");
    const QString WHITE_SQUARE = "(100, 100, 100, 100)" ;
    const QString BLACK_SQUARE = "(0, 0, 0, 100)";
};

#endif //CHESSCANVAS_H
