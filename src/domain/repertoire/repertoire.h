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

        Header() = default;

        Header(std::string name, std::string description, std::string author, const bool forWhite,
               const std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> createdAt)
            : name(std::move(name)),
              forWhite(forWhite),
              description(std::move(description)),
              author(std::move(author)),
              createdAt(createdAt) {
        }

        bool operator==(const Header &other) const {
            if (this->name != other.name) return false;
            if (this->forWhite != other.forWhite) return false;
            if (this->description != other.description) return false;
            if (this->author != other.author) return false;
            if (this->createdAt != other.createdAt) return false;
            return true;
        }
    };

    struct RepertoireData {
        Header header{};
        PositionGraph data{PositionKey(FEN::startingPosition())};

        RepertoireData() = default;

        RepertoireData(Header header, PositionGraph data) : header(std::move(header)), data(std::move(data)) {
        }

        bool operator==(const RepertoireData &other) const {
            if (this->header != other.header) return false;
            if (this->data != other.data) return false;
            return true;
        }
    };
}

Q_DECLARE_METATYPE(Domain::Types::Repertoire::RepertoireData)

Q_DECLARE_METATYPE(Domain::Types::Repertoire::Header)

#endif //CHESSREPO_REPERTOIRE_H
