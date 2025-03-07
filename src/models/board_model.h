//
// Created by Lecka on 04/03/2025.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.hpp"
#include <QAbstractTableModel>
#include <utility>

struct moveNode {
    chess::Move move;
    std::vector<moveNode> next_moves;
};

class BoardModel : public QAbstractTableModel {
public:
    explicit BoardModel(QObject* parent = nullptr): board(chess::Board()) {}

    explicit BoardModel(chess::Board& new_board, QObject* parent = nullptr): board(chess::Board(std::move(new_board))) {};

    [[nodiscard]] constexpr int rowCount(const QModelIndex &parent = QModelIndex()) const override { return 8; }
    [[nodiscard]] constexpr int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 8; }


    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool constexpr setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;


    void show_moves_for_sq(chess::Square);


    std::vector<moveNode> move_tree = {};

signals:
    void boardStateChanged();

private:
    chess::Board board;
};


#endif //CHESSBOARD_H
