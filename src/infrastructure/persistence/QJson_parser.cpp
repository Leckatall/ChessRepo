//
// Created by Lecka on 20/09/2025.
//

#include "QJson_parser.h"

#include <QJsonArray>

#include "repertoire/repertoire.h"
using namespace Domain::Types;
namespace Infrasturcture::Persistence {
    QJsonObject QJsonParser::toJson(const Repertoire::Header &header) {
        QJsonObject root;
        root["name"] = QString::fromStdString(header.name);
        root["forWhite"] = header.forWhite;
        root["createdAt"] = QJsonValue::fromVariant(QDateTime::fromStdTimePoint({header.createdAt}));
        root["author"] = QString::fromStdString(header.author);
        return root;
    }

    QJsonObject QJsonParser::toJson(const MoveEdge &edge) {
        QJsonObject root;
        root["uci_move"] = QString::fromStdString(edge.uci);
        root["target_fen"] = QString::fromStdString(edge.target.fen());
        root["comment"] = QString::fromStdString(edge.comment ? edge.comment.value(): "");
        return root;
    }

    QJsonObject QJsonParser::toJson(const PositionStats &stats) {
        QJsonObject root;
        root["games"] = stats.games;
        root["white_wins"] = stats.white_wins;
        root["draws"] = stats.draws;
        root["black_wins"] = stats.black_wins;
        return root;
    }

    QJsonObject QJsonParser::toJson(const PositionNode &node) {
        QJsonObject root;
        root["fen"] = QString::fromStdString(node.getFen());
        root["stats"] = toJson(node.stats);
        QJsonArray edgesJson;
        for (const auto &edge : node.edges) {
            edgesJson.append(toJson(edge));
        }
        return root;
    }
    QJsonObject QJsonParser::toJson(const PositionGraph &graph) {
        QJsonObject root;
        root["root_fen"] = QString::fromStdString(graph.getRootKey().fen());
        QJsonArray nodesJson;
        for (const auto &node : graph.getNodes()) {
            nodesJson.append(toJson(node));
        }
        return root;
    }

    QJsonObject QJsonParser::toJson(const Repertoire::RepertoireData &repertoire) {
        QJsonObject repJson;
        repJson["header"] = toJson(repertoire.header);
        repJson["repertoireData"] = toJson(repertoire.data);
        return repJson;
    }
}
