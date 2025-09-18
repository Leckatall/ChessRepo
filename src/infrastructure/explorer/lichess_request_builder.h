//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_LICHESS_REQUEST_BUILDER_H
#define CHESSREPO_LICHESS_REQUEST_BUILDER_H
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "domain/types/fen.h"

namespace Domain::Types {
    class FEN;
}

class QUrl;

namespace Infrastructure::Explorer {
    struct LichessRequestBuilder {
        const std::string LICHESS_URL = "https://explorer.lichess.ovh/lichess";

        enum class ConfigOption {
            Variant,
            Modes,
            Speeds,
            Ratings,
            Since,
            Until
        };

        // Struct to hold request parameters
        struct Configs {
            std::string variant = "standard";
            std::string modes = "rated";
            std::string speeds = "rapid,blitz";
            std::string ratings{};
            std::string since{};
            std::string until{};

            std::string &operator[](const ConfigOption opt) {
                switch (opt) {
                    case ConfigOption::Variant: return variant;
                    case ConfigOption::Modes: return modes;
                    case ConfigOption::Speeds: return speeds;
                    case ConfigOption::Ratings: return ratings;
                    case ConfigOption::Since: return since;
                    case ConfigOption::Until: return until;
                }
                throw std::invalid_argument("Unknown ConfigOption");
            }

            void set(std::unordered_map<ConfigOption, std::string> params) {
                for (const auto &[opt, value]: params) {
                    (*this)[opt] = value;
                }
            }

            [[nodiscard]] bool isSet(const ConfigOption &opt) { return !(*this)[opt].empty(); }

            std::unordered_map<std::string, std::string> toMap() const {
                return {
                    {"variant", variant},
                    {"modes", modes},
                    {"speeds", speeds},
                    {"ratings", ratings},
                    {"since", since},
                    {"until", until}
                };
            }
        };

        LichessRequestBuilder() = default;

        explicit LichessRequestBuilder(const Configs &conf) : config(conf) {
        }

        Configs config{};
        // Domain::Types::FEN fen = Domain::Types::FEN::startingPosition();

        [[nodiscard]] QUrl buildApiUrl(const Domain::Types::FEN &fen) const;
    };
}


#endif //CHESSREPO_LICHESS_REQUEST_BUILDER_H
