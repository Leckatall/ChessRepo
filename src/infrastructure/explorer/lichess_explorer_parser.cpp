//
// Created by Lecka on 17/09/2025.
//

#include "lichess_explorer_parser.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "domain/types/fen.h"
#include "domain/types/position/position_graph.h"
#include "domain/types/position/position_stats.h"
#include "utils/chess.h"

using namespace Infrastructure::Features::Explorer;
using namespace Domain::Types;


PositionStats LichessExplorerParser::parseStats(const QJsonObject &pos) {
    const std::int64_t white_wins = pos.value("white").toInt();
    const std::int64_t draws = pos.value("draws").toInt();
    const std::int64_t black_wins = pos.value("black").toInt();
    const std::int64_t games = white_wins + draws + black_wins;

    // TODO: Re-implement opening names and eco codes
    // Models::Opening opener;
    // if (auto openingVal = json.value("opening"); !openingVal.isNull()) {
    //     auto opening = openingVal.toObject();
    //     opener.name = opening.value("name").toString();
    //     opener.eco = opening.value("eco").toString();
    // }

    return PositionStats{games, white_wins, draws, black_wins};
}

void LichessExplorerParser::addMoveEdge(PositionGraph &graph, const FEN &start_fen, const QJsonObject &moveInfo) {
    const UCIMove uci(moveInfo.value("uci").toString().toStdString());
    const FEN result_fen = Utils::Chess::resultOfMove(start_fen, uci);
    graph.addEdge(graph.getRootKey(), {PositionKey(result_fen), parseStats(moveInfo)}, uci, "");
}

PositionGraph LichessExplorerParser::handle_reponse(const FEN &fen, const QByteArray &response) {
    const auto root = QJsonDocument::fromJson(response).object();

    PositionGraph graph(PositionKey(fen), parseStats(root));
    for (const auto &move : root.value("moves").toArray()) {
        addMoveEdge(graph, fen, move.toObject());
    }
    return graph;
}
