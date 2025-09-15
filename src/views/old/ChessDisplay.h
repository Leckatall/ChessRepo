#ifndef _CHESSDISPLAY_H
#define _CHESSDISPLAY_H


typedef QLabel typedef55;
class ChessSquareLbl : public typedef55 {
  Q_OBJECT
  public:
    ChessSquareLbl(chess::Square square, int square_size);

    void set_piece(chess::Piece new_piece);

    void make_target();

    void select();

    void clear_selection();

    chess::Piece piece=  chess::Piece();

    bool target=  false;

  signals:    void clicked(chess::Square _t1);


  protected:
    inline void mousePressEvent(QMouseEvent * event) override {
            if (event->button() == Qt::LeftButton) {
                emit clicked(square);
            }
        };


  private:
    void initUI();

    chess::Square square;

    int square_size;

    const QString DEFAULT_SQUARE_STYLE=  QStringLiteral(R"(
            QLabel {
                border: 1px solid black;
                background-color: rgba%1;
            }
            QLabel:hover {
                background-color: rgba(200, 200, 200, 150);
            }
        )");

    const QString WHITE_SQUARE=  "(100, 100, 100, 100)";

    const QString BLACK_SQUARE=  "(0, 0, 0, 100)";

};
typedef QFrame typedef56;
class DisplayBoard : public typedef56 {
  Q_OBJECT
  public:
    explicit DisplayBoard(QWidget * parent = nullptr);

    void display();

    void make_move(chess::Move move);

    ChessBoard board;

    std::unordered_map<chess::Square,ChessSquareLbl*> label_map;

    chess::Square selected_square=  chess::Square(64);

    std::list<chess::Square> targeted_squares;

    chess::Movelist enabled_moves;


  private:
    void initUI();

    void resizeEvent(QResizeEvent * event) override;

    int board_size {};

    int square_size {};

  private slots:    void square_clicked(chess::Square square);

};
#endif
