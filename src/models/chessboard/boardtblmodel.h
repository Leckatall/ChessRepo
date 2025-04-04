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
    int piece;
    bool isLight;
    bool isSelected = false;
    bool isHighlighted = false;

    explicit SquareData(const chess::Piece p = {}, const bool l = false, const bool s = false, const bool h = false)
        : piece(p),
          isLight(l),
          isSelected(s),
          isHighlighted(h) {
    }
};

Q_DECLARE_METATYPE(SquareData);

struct Move {
    QModelIndex from;
    QModelIndex to;

    explicit Move(const QModelIndex &from_index, const QModelIndex &to_index): from(from_index), to(to_index) {
    }
};

Q_DECLARE_METATYPE(Move);

// MAYBE: Could also implment a SquareModel so the flow would be BoardModel->get(index)->action();
class BoardTblModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit BoardTblModel(QObject *parent = nullptr)
        : m_board(chess::Board()) {
    }

    explicit BoardTblModel(const chess::Board &new_board, QObject *parent = nullptr)
        : m_board(chess::Board(new_board)) {
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

    [[nodiscard]] bool square_selected() const { return m_selected_square.isValid(); }
    [[nodiscard]] QString get_fen() const { return m_board.fen(); }

    // Actions to perform on the board

    void emit_update();

    void try_select(const QModelIndex &index);

    void clear_selection();

    void try_move_to(const QModelIndex &index);

    void undo_move();

    void begin_update() { beginResetModel(); }
    void end_update() { endResetModel(); }

    void flip() {
        m_white_on_bottom = !m_white_on_bottom;
    }

private:
    void select(const QModelIndex &index);

    void target(const QModelIndex &index);

    void deselect(const QModelIndex &index);

    void make_move(const QModelIndex &from, const QModelIndex &to);

    bool m_white_on_bottom = true;
    QList<Move> m_move_history = {};

    BoardWrapper m_board;

    QModelIndex m_selected_square = {};
    QSet<QModelIndex> m_target_squares;
};

#endif //CHESSBOARD_H
