
#include "ChessDisplay.h"

ChessSquareLbl::ChessSquareLbl(chess::Square square, int square_size)
    : square(square), square_size(square_size) {

    initUI();
}

void ChessSquareLbl::make_target() {

    target = true;
    this->setStyleSheet(this->styleSheet().append("QLabel {border: 5px solid red}"));
}

void ChessSquareLbl::select() {

    if(piece != chess::Piece()) {
        // If there is a piece edit style
        this->setStyleSheet(this->styleSheet().append("QLabel {border: 5px solid blue}"));
    }
}

void ChessSquareLbl::clear_selection() {

    this->setStyleSheet(DEFAULT_SQUARE_STYLE.arg(square.is_light() ? WHITE_SQUARE : BLACK_SQUARE));
}

// SIGNAL 0

void ChessSquareLbl::clicked(chess::Square _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

void ChessSquareLbl::initUI() {

    this->setGeometry(0, 0, square_size, square_size);
    QFont font = this->font();
    font.setPointSizeF(this->square_size * 0.6);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet(DEFAULT_SQUARE_STYLE.arg(square.is_light() ? WHITE_SQUARE : BLACK_SQUARE));
}

DisplayBoard::DisplayBoard(QWidget * parent)
    : QFrame(parent),
      board_size(std::min(this->width(), this->height())),
      square_size(board_size / 8),
      board(*new ChessBoard) {

    this->initUI();
}

void DisplayBoard::display() {

    // Can't belive there's no zip() in this stupid language
    for (int square_id = 0; square_id < 64; square_id++) {
        label_map[chess::Square(square_id)]->set_piece(board.at(chess::Square(square_id)));
    }
    // for (auto [square, new_value] : std::views::zip(, FEN)){
    //     square->setText(new_value);
    // }
}

void DisplayBoard::make_move() {

    std::cout << move;
    board.makeMove<true>(move);
    display();
}

void DisplayBoard::initUI() {

    auto board_layout = new QGridLayout();
    board_layout->setSpacing(0);

    // auto *square = new ChessSquare(1, true, this->square_size);
    // board_layout->addWidget(square);
    for (int row = 0; row < 8; ++row) {
        const auto rank = chess::Rank(7 - row);
        for (int col = 0; col < 8; ++col) {
            const auto file = chess::File(col);
            const auto square = chess::Square(rank, file);
            auto *squareLbl = new ChessSquareLbl(square, this->square_size);
            label_map[square] = squareLbl;
            board_layout->addWidget(squareLbl, row, col);
            connect(squareLbl, &ChessSquareLbl::clicked, this, &DisplayBoard::square_clicked);
        }
    }
    this->setLayout(board_layout);
}

void DisplayBoard::resizeEvent() {

    QFrame::resizeEvent(event);

    int l = std::min(this->width(), this->height());
    QPoint center = this->rect().center();
    auto rect = new QRect(0, 0, l, l);
    rect->moveCenter(center);
    this->setGeometry(*rect);
}

