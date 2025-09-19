//
// Created by Lecka on 17/09/2025.
//

#include "uci_move.h"

#include <regex>

namespace Domain::Types {
    bool UCIMove::isValid(const std::string &move) {
        static const std::regex uci_regex(
            R"(^[a-h][1-8][a-h][1-8][qrbn]?$)"
        );
        return std::regex_match(move, uci_regex);
    }

    std::string UCIMove::from() const { return this->substr(0, 2); }

    std::string UCIMove::to() const { return this->substr(2, 2); }

    char UCIMove::promotion() const { return this->length() > 4 ? (*this)[4] : '\0'; }
}

std::size_t std::hash<Domain::Types::UCIMove>::operator()(const Domain::Types::UCIMove &uci) const noexcept {
    return hash<std::string>{}(uci);
}
