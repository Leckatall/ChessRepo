//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_IEXPLORER_SERVICE_H
#define CHESSREPO_IEXPLORER_SERVICE_H
#include <functional>
#include <optional>
#include <string>

namespace Domain::Types {
    class UCIMove;
    struct PositionStats;
    class FEN;
}

namespace Domain::Explorer {
    struct IExplorerService {
        virtual ~IExplorerService() = default;

        virtual void fetchOpeningData(const Types::FEN& fen,
                                      std::optional<Types::UCIMove> play,
                                      std::function<void(const Types::PositionStats&,
                                                         const std::vector<Types::PositionStats>&)> onSuccess,
                                      std::function<void(std::string)> onError) = 0;

    };

}

#endif //CHESSREPO_IEXPLORER_SERVICE_H