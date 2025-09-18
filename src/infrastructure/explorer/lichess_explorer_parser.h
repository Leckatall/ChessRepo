//
// Created by Lecka on 17/09/2025.
//

#ifndef CHESSREPO_LICHESS_EXPLORER_PARSER_H
#define CHESSREPO_LICHESS_EXPLORER_PARSER_H

#include <QJsonObject>

#include "domain/types/position/position_stats.h"

namespace Domain::Types {
    class FEN;
    class UCIMove;
    class PositionGraph;
}

namespace Infrastructure::Features::Explorer {
    class LichessExplorerParser {
    public:
        static Domain::Types::PositionGraph handle_reponse(const Domain::Types::FEN &fen, const QByteArray &response);
    private:
        static Domain::Types::PositionStats parseStats(const QJsonObject &pos);

        static void addMoveEdge(Domain::Types::PositionGraph &graph, const Domain::Types::FEN &start_fen,
                                const QJsonObject &moveInfo);
    };
}

#endif //CHESSREPO_LICHESS_EXPLORER_PARSER_H