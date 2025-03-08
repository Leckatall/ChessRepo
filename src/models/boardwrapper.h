//
// Created by Lecka on 07/03/2025.
//

#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <chess.hpp>
#include <qmetatype.h>
#include <QString>
#include <QModelIndex>


// Stupid language needs me to tell it how to hash the easiest to hash thing in the world...
namespace std {
    template<>
    struct hash<chess::Square> {
        size_t operator()(const chess::Square &s) const noexcept {
            return static_cast<size_t>(s.index()); // Convert to integer index
        }
    };
}


class BoardWrapper : public chess::Board {
public:
    BoardWrapper() = default;

    explicit BoardWrapper(const Board& new_board): Board(new_board) {
    }
    // Helper methods
    [[nodiscard]] static chess::Square square(const QModelIndex &index) {
        return {(index.row() * 8) + index.column()};
    }

    [[nodiscard]] static chess::Move move(const QModelIndex &from, const QModelIndex &to) {
        return chess::Move::make(square(from), square(to));
    }
    // Simple wrappers
    void undo_move(const QModelIndex &from, const QModelIndex &to) {
        return unmakeMove(move(from, to));
    }

    void make_move(const QModelIndex &from, const QModelIndex &to) {
        return makeMove(move(from, to));
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
};


#endif //BOARDMODEL_H
