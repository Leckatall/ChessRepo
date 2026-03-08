//
// Created by Lecka on 04/03/2025.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.hpp"
#include <utility>

#include "board_wrapper.h"
#include "chess/board.h"
#include "domain/types/uci_move.h"
#include "models/datatypes.h"

struct SquareData {
    Domain::Types::Chess::PieceType piece;
    bool isLight;
    bool isSelected = false;
    bool isHighlighted = false;

    explicit SquareData(const Domain::Types::Chess::PieceType p = {}, const bool l = false, const bool s = false, const bool h = false)
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
        explicit TblModel(const Domain::Features::Chess::Board &board, QObject *parent = nullptr)
            : QAbstractTableModel(parent),
              m_board(board) {
        }

        // Helper methods
        [[nodiscard]] QModelIndex square_to_index(const chess::Square &square) const {
            return index(square.rank(), square.file());
        }
        [[nodiscard]] static chess::Square index_to_square(const QModelIndex &index) {
            return {index.row() * 8 + index.column()};
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

        [[nodiscard]] bool square_selected() const { return m_selected_square.isValid(); }
        [[nodiscard]] QModelIndex get_selected_square() const { return m_selected_square; }

        void try_select(const QModelIndex &index);

        void clear_selection();

        void begin_update() { beginResetModel(); }
        void end_update() { endResetModel(); }

    public slots:

        void set_state(const Domain::Features::Chess::Board &board);

        void emit_update();

    private:
        void select(const QModelIndex &index);

        void target(const QModelIndex &index);

        void deselect(const QModelIndex &index);


        Domain::Features::Chess::Board m_board;

        QModelIndex m_selected_square = {};
        QSet<QModelIndex> m_target_squares;
    };
}


#endif //CHESSBOARD_H
