//
// Created by Lecka on 18/09/2025.
//

#ifndef CHESSREPO_POSITION_GRAPH_H
#define CHESSREPO_POSITION_GRAPH_H
#include <algorithm>
#include <memory>
#include <optional>
#include <span>
#include <unordered_map>

#include "position_key.h"
#include "position_stats.h"
#include "domain/types/uci_move.h"

namespace Domain::Types {
    struct PositionNode;

    struct MoveEdge {
        UCIMove uci;
        PositionKey target;
        std::optional<std::string> comment;

        MoveEdge(const UCIMove &uci, const PositionKey &target, std::string comment)
            : uci(uci),
              target(target),
              comment(std::move(comment)) {
        }
    };

    struct PositionNode {
        PositionKey key;
        PositionStats stats;
        std::vector<MoveEdge> edges{};

        PositionNode(PositionKey k, PositionStats s) : key(std::move(k)), stats(std::move(s)) {
        }

        bool addEdge(const MoveEdge &edge) {
            if (hasMove(edge.uci)) return false;
            edges.emplace_back(edge);
            return true;
        }

        bool addEdge(const UCIMove &move, PositionKey target, std::string comment = "") {
            return addEdge({move, std::move(target), std::move(comment)});
        }

        [[nodiscard]] const MoveEdge *findMove(const UCIMove &move) const {
            const auto it = std::ranges::find_if(edges, [&](const MoveEdge &e) { return e.uci == move; });
            return (it != edges.end()) ? &*it : nullptr;
        }

        MoveEdge *findMove(const UCIMove &move) {
            const auto it = std::ranges::find_if(edges, [&](MoveEdge &e) { return e.uci == move; });
            return (it != edges.end()) ? &*it : nullptr;
        }

        bool removeEdge(const UCIMove &move) {
            const auto it = std::ranges::remove_if(edges, [&](const MoveEdge &e) { return e.uci == move; }).begin();
            if (it == edges.end()) return false;
            edges.erase(it, edges.end());
            return true;
        }

        [[nodiscard]] bool hasMove(const UCIMove &move) const { return findMove(move) != nullptr; }
        [[nodiscard]] size_t edgeCount() const { return edges.size(); }

        [[nodiscard]] FEN getFen() const {return key.fen();}
    };

    class PositionGraph {
    public:
        explicit PositionGraph(const PositionNode &root);

        explicit PositionGraph(const PositionKey &rootKey, const PositionStats &rootStats = {});

        const PositionNode *getNode(const PositionKey &key) const;

        PositionNode *getNode(const PositionKey &key);

        void addNode(const PositionNode &node);

        void addNode(const PositionKey& key, const PositionStats &stats);

        bool hasNode(const PositionKey &key) const;

        void ensureNode(const PositionNode &node);

        void ensureNode(const PositionKey &key, PositionStats stats);

        size_t nodeCount() const;

        const PositionKey &getRootKey() const;

        bool addEdgeToNodes(const PositionKey &from, const PositionKey &to, const UCIMove &move, std::string comment);

        bool addEdge(const PositionKey &from, const PositionNode &to, const UCIMove &move, std::string comment);

        std::span<const MoveEdge> getEdges(const PositionKey &key) const;

        PositionStats getMoveStats(const PositionKey &from, const UCIMove &move) const;

        PositionStats getStats(const MoveEdge &moveEdge) const;

    private:
        std::unordered_map<PositionKey, PositionNode* > m_nodes{};
        PositionKey m_rootKey;
    };
}

Q_DECLARE_METATYPE(Domain::Types::PositionGraph);


#endif //CHESSREPO_POSITION_GRAPH_H
