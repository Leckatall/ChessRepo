//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_UCI_MOVE_H
#define CHESSREPO_UCI_MOVE_H
#include <qmetatype.h>
#include <stdexcept>
#include <string>


namespace Domain::Types {
    class UCIMove : public std::string {
    public:
        explicit UCIMove(const std::string &move) : std::string(move) {
            if (!isValid(move)) {
                throw std::invalid_argument("Invalid UCI move");
            }
        }

        [[nodiscard]] static bool isValid(const std::string &move);

        [[nodiscard]] std::string from() const;

        [[nodiscard]] std::string to() const;

        [[nodiscard]] char promotion() const;
    };
}
Q_DECLARE_METATYPE(Domain::Types::UCIMove)

namespace std {
    template<> struct hash<Domain::Types::UCIMove> {
        size_t operator()(const Domain::Types::UCIMove& uci) const noexcept;
    };
}

#endif //CHESSREPO_UCI_MOVE_H