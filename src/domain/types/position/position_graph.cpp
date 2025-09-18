//
// Created by Lecka on 18/09/2025.
//

#include "position_graph.h"

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
        if (const auto it = m_nodes.find(key); it != m_nodes.end()) return it->second.get();
        return nullptr;
    }

    PositionNode * PositionGraph::getNode(const PositionKey &key) {
        if (const auto it = m_nodes.find(key); it != m_nodes.end()) return it->second.get();
        return nullptr;
    }

    void PositionGraph::addNode(const PositionNode& node) {
        m_nodes[node.key] = std::make_unique<PositionNode>(node);
    }
    void PositionGraph::addNode(PositionKey key, PositionStats stats) {
        m_nodes[key] = std::make_unique<PositionNode>(key, stats);
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

    // Get edges from a position
    const std::vector<MoveEdge> &PositionGraph::getEdges(const PositionKey &key) const {
        static const std::vector<MoveEdge> kEmpty;
        const auto* node = getNode(key);
        return node ? node->edges : kEmpty;
    }
}

