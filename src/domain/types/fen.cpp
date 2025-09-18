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

    std::vector<std::string> FEN::components() const {
        std::vector<std::string> parts;
        std::istringstream iss(*this);
        std::string part;
        while (iss >> part) {
            parts.push_back(part);
        }
        return parts;
    }
    std::string FEN::boardState() const {
        return components()[0];
    }

    std::string FEN::activeColor() const {
        return components()[1];
    }

    std::string FEN::castlingRights() const {
        return components()[2];
    }

    std::string FEN::enPassantTarget() const {
        return components()[3];
    }

    int FEN::halfmoveClock() const {
        return std::stoi(components()[4]);
    }

    int FEN::fullmoveNumber() const {
        return std::stoi(components()[5]);
    }

    std::string FEN::aggregatedKey() const {
        auto parts = components();
        return parts[0] + " " + parts[1] + " " + parts[2] + " " + parts[3];
    }
}
