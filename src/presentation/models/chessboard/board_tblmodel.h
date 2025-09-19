//
// Created by Lecka on 04/03/2025.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.hpp"
#include <utility>

#include "board_wrapper.h"
#include "domain/types/uci_move.h"
#include "models/datatypes.h"

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

namespace chessboard {
    // MAYBE: Could also implment a SquareModel so the flow would be BoardModel->get(index)->action();
    class TblModel : public QAbstractTableModel {
        Q_OBJECT

    public:
        explicit TblModel(QObject *parent = nullptr)
            : QAbstractTableModel(parent),
              m_board(chess::Board()) {
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
        void try_select(const QModelIndex &index);

        void clear_selection();

        void try_move_to(const QModelIndex &index);

        void make_move(Models::Move m);

        void undo_move();

        void begin_update() { beginResetModel(); }
        void end_update() { endResetModel(); }

        QList<Models::Move> get_history() {
            return m_board.get_history();
        }

    public slots:
        void makeUciMove(const Domain::Types::UCIMove &uci);

        void emit_update();

    signals:
        void boardUpdated();

    private:
        void select(const QModelIndex &index);

        void target(const QModelIndex &index);

        void deselect(const QModelIndex &index);

        void make_move(const QModelIndex &from, const QModelIndex &to);

        template<typename... Args>
        void makeMove(Args &&... args);

        Board m_board;

        QModelIndex m_selected_square = {};
        QSet<QModelIndex> m_target_squares;
    };
}


#endif //CHESSBOARD_H
