//
// Created by Lecka on 15/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_TREE_H
#define CHESSREPO_REPERTOIRE_TREE_H
#include <QList>
#include <QMap>
#include <QString>
#include <utility>

#include "chess_primitives.h"

namespace Models::RepTree {
    struct PositionNode;

    struct MoveEdge {
        UCIMove uci;
        FEN child_fen;
        QString comment;

        MoveEdge(UCIMove m, FEN child, QString c = {})
            : uci(std::move(m)), child_fen(std::move(child)), comment(std::move(c)) {
        }

        bool operator==(const MoveEdge &other) const {
            return uci == other.uci;
        }
    };

    struct PositionNode {
        FEN fen;
        QMap<UCIMove, MoveEdge> move_edges;
        QList<FEN> parents;
        explicit PositionNode(FEN pos = FEN::startingPosition())
            : fen(std::move(pos)) {
        }
    };

    struct RepertoireTree {
        std::unique_ptr<PositionNode> root;
        QMap<FEN, std::unique_ptr<PositionNode>> positions;

        explicit RepertoireTree(PositionNode root = PositionNode())
            : root(std::make_unique<PositionNode>(std::move(root))) {
        }
    };
} // Models

#endif //CHESSREPO_REPERTOIRE_TREE_H