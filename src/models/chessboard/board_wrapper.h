//
// Created by Lecka on 07/03/2025.
//

#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <chess.hpp>
#include <qmetatype.h>
#include <QString>
#include <QModelIndex>

#include "models/datatypes.h"


// Stupid language needs me to tell it how to hash the easiest to hash thing in the world...
namespace std {
    template<>
    struct hash<chess::Square> {
        size_t operator()(const chess::Square &s) const noexcept {
            return static_cast<size_t>(s.index()); // Convert to integer index
        }
    };
}

namespace chessboard {
    class Board : public chess::Board {
    public:
        Board() = default;

        explicit Board(const chess::Board &new_board): chess::Board(new_board) {
        }

        // Helper methods
        [[nodiscard]] static chess::Square square(const QModelIndex &index) {
            return {index.row() * 8 + index.column()};
        }

        [[nodiscard]] static chess::Move move(const QModelIndex &from, const QModelIndex &to) {
            return chess::Move::make(square(from), square(to));
        }

        [[nodiscard]] chess::Move move(const Models::Move &m) const {
            return chess::uci::uciToMove(*this, m.uci.toStdString());
        }

        [[nodiscard]] Models::Move moveModel(const chess::Move m) const {
            QString uci = QString::fromStdString(chess::uci::moveToUci(m));
            QString san = QString::fromStdString(chess::uci::moveToSan(*this, m));
            return {uci, san};
        }

        // Simple wrappers
        [[nodiscard]] QString fen() const {
            return QString::fromStdString(getFen());
        }

        bool make_move(chess::Move m);

        bool make_move(const Models::Move &m) {
            // Shouldn't be an override like this should have this be the only method making moves
            return make_move(chess::uci::uciToMove(*this, m.uci.toStdString()));
        }

        bool make_move(const QModelIndex &from, const QModelIndex &to) {
            return make_move(moveModel(move(from, to)));
        }

        [[nodiscard]] chess::Piece get_piece(const QModelIndex &index) const {
            return at(square(index));
        }

        // Complex wrappers
        [[nodiscard]] bool isWhiteMove() const { return this->sideToMove() == chess::Color("w"); }

        [[nodiscard]] QSet<chess::Square> get_legal_targets_for(const chess::Square &square) const;

        [[nodiscard]] QSet<chess::Square> get_legal_targets_for(const QModelIndex &index) const {
            return get_legal_targets_for(square(index));
        }

        [[nodiscard]] bool is_enabled_square(const chess::Square &square) const;

        [[nodiscard]] bool is_enabled_square(const QModelIndex &index) const {
            return is_enabled_square(square(index));
        }

        // New Functionality
        QList<Models::Move> get_history() { return m_move_history; }

        bool undo_last_move();

    private:
        bool undo_move(const Models::Move &m);

        QList<Models::Move> m_move_history = {};
    };
}


#endif //BOARDMODEL_H
