//
// Created by Lecka on 04/03/2025.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.hpp"
#include <QAbstractTableModel>
#include <QString>
#include <utility>

#include "boardwrapper.h"

struct SquareData {
    QString piece;
    bool isLight;
    bool isSelected = false;
    bool isHighlighted = false;

    explicit SquareData(const chess::Piece p = {}, const bool l = false, const bool s = false, const bool h = false)
        : piece(QString::fromStdString(std::string(p))),
          isLight(l),
          isSelected(s),
          isHighlighted(h) {
    }
};

Q_DECLARE_METATYPE(SquareData);

// MAYBE: Could also implment a SquareModel so the flow would be BoardModel->get(index)->action();
class BoardTblModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit BoardTblModel(QObject *parent = nullptr)
        : m_board(chess::Board()) {
    }

    explicit BoardTblModel(chess::Board new_board, QObject *parent = nullptr)
        : m_board(chess::Board(std::move(new_board))) {
    }

    // Helper methods
    [[nodiscard]] QModelIndex square_to_index(const chess::Square &square) const {
        return index(square.rank(), square.file());
    }


    // Get table info

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override { return 8; }

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override { return 8; }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] QVariant
    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Set table info
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;


    // Data to get from the board
    [[nodiscard]] QSet<QModelIndex> get_legal_targets_from(const QModelIndex &index) const;

    // Actions to perform on the board
    void select(const QModelIndex &index);
    void target(const QModelIndex &index);
    void deselect(const QModelIndex &index);

    void update_selections(const QModelIndex &sel, const QSet<QModelIndex> &targets);

    void make_move(const QModelIndex &from, const QModelIndex &to);
    void undo_move(const QModelIndex &from, const QModelIndex &to);

private:
    BoardWrapper m_board;
    QModelIndex m_selected_square = {};
    QSet<QModelIndex> m_targeted_squares;
};

#endif //CHESSBOARD_H
