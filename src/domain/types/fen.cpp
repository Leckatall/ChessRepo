//
// Created by Lecka on 17/09/2025.
//

#include "fen.h"
#include <regex>
#include <stdexcept>


namespace Domain::Types {
    FEN::FEN(const std::string &fen): std::string(fen) {
        if (!isValid(fen)) {
            throw std::invalid_argument("Invalid FEN string");
        }
    }

    bool FEN::isValid(const std::string &fen) {
        static const std::regex fen_regex(
            R"(^([rnbqkpRNBQKP1-8]{1,8}/){7}[rnbqkpRNBQKP1-8]{1,8} [wb] (K?Q?k?q?|-) ([a-h][36]|-) \d+ \d+$)"
        );
        return std::regex_match(fen, fen_regex);
    }

    FEN FEN::startingPosition() {
        return FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    FEN FEN::emptyBoard() {
        return FEN("8/8/8/8/8/8/8/8 w - - 0 1");
    }
}
