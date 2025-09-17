//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_FEN_H
#define CHESSREPO_FEN_H
#include <string>

namespace Domain::Types {
    class FEN : public std::string {
    public:
        explicit FEN(const std::string &fen);

        std::string board() const;

        [[nodiscard]] static bool isValid(const std::string &fen);

        static FEN startingPosition();

        static FEN emptyBoard();


    };
}

#endif //CHESSREPO_FEN_H
