//
// Created by Lecka on 17/09/2025.
//

#include "uci_move.h"

#include <regex>

namespace Domain::Types {
    bool UCIMove::isValid(const std::string &move) {
        static const std::regex fen_regex(
            R"(^([rnbqkpRNBQKP1-8]{1,8}/){7}[rnbqkpRNBQKP1-8]{1,8} [wb] (K?Q?k?q?|-) ([a-h][36]|-) \d+ \d+$)"
        );
        return std::regex_match(move, fen_regex);

    }

    std::string UCIMove::from() const { return this->substr(0, 2); }

    std::string UCIMove::to() const { return this->substr(2, 2); }

    char UCIMove::promotion() const { return this->length() > 4 ? (*this)[4] : '\0'; }
}
