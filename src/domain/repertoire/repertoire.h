//
// Created by Lecka on 19/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_H
#define CHESSREPO_REPERTOIRE_H
#include <string>
#include <chrono>

#include "domain/types/position/position_graph.h"

namespace Domain::Types::Repertoire {
    struct Header {
        std::string name;
        bool forWhite{true};
        std::string description;
        std::string author;
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> createdAt;
    };
    struct RepertoireData {
        Header header{};
        PositionGraph data{};

        RepertoireData() = default;
        RepertoireData(Header header, PositionGraph data) : header(std::move(header)), data(std::move(data)) {}
    };
}
Q_DECLARE_METATYPE(Domain::Types::Repertoire::RepertoireData)
Q_DECLARE_METATYPE(Domain::Types::Repertoire::Header)

#endif //CHESSREPO_REPERTOIRE_H