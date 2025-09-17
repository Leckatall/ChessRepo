//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_IEXPLORER_SERVICE_H
#define CHESSREPO_IEXPLORER_SERVICE_H

namespace Domain::Explorer {
    struct IExplorerService {
        virtual ~IExplorerService() = default;

        // async API options — pick one pattern for your app
        // 1) Callback-based
        virtual void fetchOpeningData(const Types::FEN& fen,
                                      std::optional<Types::UCIMove> play,
                                      std::function<void(const Types::PositionStats&,
                                                         const std::vector<Types::MoveStats>&)> onSuccess,
                                      std::function<void(std::string)> onError) = 0;

        // or 2) Return a task/future/promise if you use such infra
    };

}

#endif //CHESSREPO_IEXPLORER_SERVICE_H