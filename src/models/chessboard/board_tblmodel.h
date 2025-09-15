#ifndef _BOARD_TBLMODEL_H
#define _BOARD_TBLMODEL_H


struct SquareData {
    int piece;

    bool isLight;

    bool isSelected=  false;

    bool isHighlighted=  false;

    inline explicit SquareData(const chess::Piece p = {}, const bool l = false, const bool s = false, const bool h = false) : piece(p),
              isLight(l),
              isSelected(s),
              isHighlighted(h) {
        };

};
#endif
