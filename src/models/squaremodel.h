//
// Created by Lecka on 08/03/2025.
//

#ifndef SQUAREMODEL_H
#define SQUAREMODEL_H
#include <chess.hpp>
#include <QObject>


class SquareModel: public QObject {
Q_OBJECT
public:
    SquareModel();
    void select();
    void target();
    void deselect();

private:
    chess::Square m_square;
    chess::Piece m_piece = {};
    bool isSelected = false;
    bool isTargeted = false;
};



#endif //SQUAREMODEL_H
