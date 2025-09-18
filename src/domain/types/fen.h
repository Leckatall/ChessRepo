//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_FEN_H
#define CHESSREPO_FEN_H
#include <string>
#include <vector>

namespace Domain::Types {
    class FEN : public std::string {
    public:
        explicit FEN(const std::string &fen);

        [[nodiscard]] static bool isValid(const std::string &fen);

        static FEN startingPosition();

        static FEN emptyBoard();

        [[nodiscard]] std::string boardState() const; // Just the piece placement
        [[nodiscard]] std::string activeColor() const; // w/b
        [[nodiscard]] std::string castlingRights() const; // KQkq or subset
        [[nodiscard]] std::string enPassantTarget() const; // - or square
        [[nodiscard]] int halfmoveClock() const; // 50-move rule counter
        [[nodiscard]] int fullmoveNumber() const; // Move number

        // Convenience method for aggregated comparison key
        [[nodiscard]] std::string aggregatedKey() const;

    private:
        // Helper to parse FEN components
        [[nodiscard]] std::vector<std::string> components() const;
    };
}

#endif //CHESSREPO_FEN_H
