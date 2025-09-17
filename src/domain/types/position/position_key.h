//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_POSITION_KEY_H
#define CHESSREPO_POSITION_KEY_H
#include "../fen.h"

namespace Domain::Types {
    enum class PositionIdentityPolicy { RulesAccurate, Aggregated };

    class PositionKey {
    public:
        explicit PositionKey(FEN fen, PositionIdentityPolicy policy = PositionIdentityPolicy::RulesAccurate);

        const FEN &fen() const noexcept { return m_fen; }
        PositionIdentityPolicy policy() const noexcept { return m_policy; }

        // Equality/hash reflect the chosen policy (e.g., ignore halfmove/fullmove for Aggregated)
        bool operator==(const PositionKey &other) const noexcept;

    private:
        FEN m_fen;
        PositionIdentityPolicy m_policy;
    };
}

// TODO: Implement hashing
// namespace std {
//     template<> struct hash<Domain::Types::PositionKey> {
//         size_t operator()(const Domain::Types::PositionKey& k) const noexcept;
//     };
// }

#endif //CHESSREPO_POSITION_KEY_H
