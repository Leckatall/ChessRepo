//
// Created by Lecka on 04/03/2025.
//

#ifndef BUILDREPOFRAME_H
#define BUILDREPOFRAME_H
#include <chess.hpp>
#include <QFrame>

class BuildRepoFrame : public QFrame {
    Q_OBJECT

public:
    void initUI();
    void initLayout();

    void add_move(chess::Move move);
    void remove_move(chess::Move move);


};

#endif //BUILDREPOFRAME_H
