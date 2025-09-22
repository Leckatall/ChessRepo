//
// Created by Lecka on 18/09/2025.
//

#include "position_graph.h"

#include <ranges>
#include <span>

#include "utils/chess.h"

namespace Domain::Types {
    PositionGraph::PositionGraph(const PositionNode &root)
    : m_rootKey(root.key) {
        addNode(root);
    }

    PositionGraph::PositionGraph(const PositionKey &rootKey, const PositionStats &rootStats)
        : m_rootKey(rootKey) {
        addNode(rootKey, rootStats);
    }

    const PositionNode * PositionGraph::getNode(const PositionKey &key) const {
        if (const auto it = m_nodes.find(key); it != m_nodes.end()) return it->second;
        return nullptr;
    }

    PositionNode * PositionGraph::getNode(const PositionKey &key) {
        if (const auto it = m_nodes.find(key); it != m_nodes.end()) return it->second;
        return nullptr;
    }

    void PositionGraph::addNode(const PositionNode& node) {
        m_nodes[node.key] = new PositionNode(node);
    }
    void PositionGraph::addNode(const PositionKey& key, const PositionStats &stats) {
        m_nodes[key] = new PositionNode(key, stats);
    }
    // Utility methods
    bool PositionGraph::hasNode(const PositionKey &key) const {
        return m_nodes.contains(key);
    }

    void PositionGraph::ensureNode(const PositionNode &node) {
        if (hasNode(node.key)) return;
        addNode(node);
    }

    void PositionGraph::ensureNode(const PositionKey &key, PositionStats stats) {
        if (hasNode(key)) return;
        addNode(key, stats);
    }

    size_t PositionGraph::nodeCount() const {
        return m_nodes.size();
    }

    const PositionKey& PositionGraph::getRootKey() const {
        return m_rootKey;
    }

    // Add edge between existing nodes
    bool PositionGraph::addEdgeToNodes(const PositionKey &from, const PositionKey &to, const UCIMove& move, std::string comment) {
        auto* fromNode = getNode(from);
        if (!fromNode || !hasNode(to)) {
            return false;
        }

        return fromNode->addEdge({move, to, std::move(comment)});;
    }

    bool PositionGraph::addEdge(const PositionKey &from, const PositionNode &to, const UCIMove &move,
        std::string comment) {
        if (!getNode(from)) return false;
        ensureNode(to);
        return addEdgeToNodes(from, to.key, move, std::move(comment));
    }

    bool PositionGraph::addMoveFromNode(const PositionKey &from, const UCIMove &move, const PositionStats &toStats,
        std::string comment) {
        auto* fromNode = getNode(from);
        if (!fromNode) return false;
        const auto toFEN = Utils::Chess::resultOfMove(from.fen(), move);
        const PositionKey toKey(toFEN, from.policy());
        ensureNode(toKey, toStats);
        return fromNode->addEdge({move, toKey, std::move(comment)});
    }

    // Get edges from a position
    std::span<const MoveEdge> PositionGraph::getEdges(const PositionKey &key) const {
        // Old vector implementation
        // static const std::vector<MoveEdge> kEmpty;
        // const auto* node = getNode(key);
        // return node ? node->edges : kEmpty;
        const auto* node = getNode(key);
        return node ? std::span(node->edges) : std::span<const MoveEdge>();
    }

    PositionStats PositionGraph::getMoveStats(const PositionKey &from, const UCIMove &move) const {
        const auto origin = getNode(from);
        if (!origin) return {};
        const auto moveEdge = origin->findMove(move);
        if (!moveEdge) return {};

        return getStats(*moveEdge);
    }

    PositionStats PositionGraph::getStats(const MoveEdge &moveEdge) const {
        const auto target = getNode(moveEdge.target);
        if (!target) return {};
        return target->stats;
    }

    std::vector<PositionNode> PositionGraph::getNodes() const {
        std::vector<PositionNode> nodes;
        nodes.reserve(m_nodes.size());
        for (const auto &node: m_nodes | std::views::values) {
            nodes.push_back(*node);
        }
        return nodes;
    }

    PositionGraph PositionGraph::getSubGraph(PositionKey from) {
        PositionGraph subGraph(from, getNode(from)->stats);
        for (const auto &edge: getEdges(from)) {
            subGraph << getSubGraph(edge.target);
            subGraph.addEdgeToNodes(from, edge.target, edge.uci, edge.comment.value());
        }
        return subGraph;
    }

    bool PositionGraph::operator==(const PositionGraph &other) const {
        if (this->m_rootKey != other.m_rootKey) return false;
        if (this->m_nodes.size() != other.m_nodes.size()) return false;
        for (const auto &[position_key, node]: m_nodes) {
            if (!other.m_nodes.contains(position_key)) return false;
            if (node->stats != other.m_nodes.at(position_key)->stats) return false;
        }
        return true;
    }

    void PositionGraph::operator<<(const PositionGraph &other) {
        for (const auto& [k, v] : other.m_nodes) {
            m_nodes[k] = v;
        }
    }
}

