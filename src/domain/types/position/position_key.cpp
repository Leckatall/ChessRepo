//
// Created by Lecka on 17/09/2025.
//

#include "position_key.h"

namespace Domain::Types {
    bool PositionKey::operator==(const PositionKey &other) const noexcept {
            if (m_policy != other.m_policy) return false;
            // if (m_policy == PositionIdentityPolicy::RulesAccurate)
                return m_fen == other.m_fen;
            //  TODO: implement Aggregated: compare only relevant parts
            // return m_fen.piecePlacement == rhs.m_fen.piecePlacement &&
            //        m_fen.sideToMove    == rhs.m_fen.sideToMove &&
            //        m_fen.castling      == rhs.m_fen.castling &&
            //        m_fen.enPassant     == rhs.m_fen.enPassant;
        }
    }