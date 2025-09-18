//
// Created by Lecka on 17/09/2025.
//

#include "position_key.h"

namespace Domain::Types {
    bool PositionKey::operator==(const PositionKey &other) const noexcept {
        if (m_policy != other.m_policy) return false;
        if (m_policy == PositionIdentityPolicy::RulesAccurate)
            return m_fen == other.m_fen;
        return m_fen.aggregatedKey() == other.m_fen.aggregatedKey();
    }
}

std::size_t std::hash<Domain::Types::PositionKey>::operator()(const Domain::Types::PositionKey &k) const noexcept {
    const size_t policyHash = hash<int>{}(static_cast<int>(k.policy()));
    size_t fenHash;

    switch (k.policy()) {
        case Domain::Types::PositionIdentityPolicy::RulesAccurate:
            fenHash = hash<string>{}(k.fen());
            break;

        case Domain::Types::PositionIdentityPolicy::Aggregated:
            fenHash = hash<string>{}(k.fen().aggregatedKey());
            break;
    }

    // Combine hashes
    return policyHash ^ (fenHash << 1);
}
