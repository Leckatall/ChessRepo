//
// Created by Lecka on 18/09/2025.
//

#ifndef CHESSREPO_UITLS_H
#define CHESSREPO_UITLS_H
#include <QString>
#include "../domain/types/fen.h"
#include "../domain/types/uci_move.h"
#include <chess.hpp>

namespace Presentation::Utils {
    inline QString formatPercentage(double value, int precision = 2) {
        return QString::number(value * 100, 'f', precision) + "%";
    }
    inline QString toPercentage(const int numerator, int denominator, const int precision  = 2) {
        return formatPercentage(numerator / static_cast<double>(denominator), precision);
    }
    inline QString toPercentage(const std::int64_t numerator, const std::int64_t denominator, const int precision  = 2) {
        return formatPercentage(numerator / static_cast<double>(denominator), precision);
    }

    inline QString toPercentage(const double numerator, const double denominator) {
        return formatPercentage(numerator / denominator);
    }
    inline QString uciToSan(const Domain::Types::FEN &fen, const Domain::Types::UCIMove &move) {
        const chess::Board board(fen);
        return QString::fromStdString(chess::uci::moveToSan(board, chess::uci::uciToMove(board, move)));
    }
}
#endif //CHESSREPO_UITLS_H