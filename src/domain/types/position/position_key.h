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
        explicit PositionKey(const FEN &fen, const PositionIdentityPolicy policy = PositionIdentityPolicy::Aggregated)
            :m_fen(fen), m_policy(policy) {}

        [[nodiscard]] const FEN &fen() const noexcept { return m_fen; }
        [[nodiscard]] PositionIdentityPolicy policy() const noexcept { return m_policy; }

        // Equality/hash reflect the chosen policy (e.g., ignore halfmove/fullmove for Aggregated)
        bool operator==(const PositionKey &other) const noexcept;

    private:
        FEN m_fen;
        PositionIdentityPolicy m_policy;
    };
}

namespace std {
    template<> struct hash<Domain::Types::PositionKey> {
        size_t operator()(const Domain::Types::PositionKey& k) const noexcept;
    };
}

#endif //CHESSREPO_POSITION_KEY_H
