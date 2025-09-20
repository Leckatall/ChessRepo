//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_QJSON_PARSER_H
#define CHESSREPO_QJSON_PARSER_H
#include <QJsonObject>

namespace Domain::Types {
    class PositionGraph;
    struct PositionNode;
    struct PositionStats;
    struct MoveEdge;
    namespace Repertoire {
        struct Header;
        struct RepertoireData;
    }
}

namespace Infrasturcture::Persistence {
    struct QJsonParser {
        static QJsonObject toJson(const Domain::Types::Repertoire::Header &header);

        static QJsonObject toJson(const Domain::Types::MoveEdge &edge);

        static QJsonObject toJson(const Domain::Types::PositionStats &stats);

        static QJsonObject toJson(const Domain::Types::PositionNode &node);

        static QJsonObject toJson(const Domain::Types::PositionGraph &graph);

        static QJsonObject toJson(const Domain::Types::Repertoire::RepertoireData &repertoire);
    };
}


#endif //CHESSREPO_QJSON_PARSER_H