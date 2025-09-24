//
// Created by Lecka on 21/09/2025.
//

#include "repertoire_viewmodel.h"

#include "utils/chess.h"

namespace Presentation::Features::Repertoire {
    RepertoireViewModel::RepertoireViewModel(Domain::Types::Repertoire::RepertoireData &repertoire, QObject *parent)
        : QObject(parent),
          m_repertoire(repertoire) {
        onPositionChanged(Domain::Types::FEN::startingPosition());
    }

    void RepertoireViewModel::setRepertoire(
        const Domain::Types::Repertoire::RepertoireData &repertoire) {
        m_repertoire = repertoire;
        onPositionChanged(Domain::Types::FEN::startingPosition());
        // emit repertoireChanged(m_repertoire); no one cares abt that only that the next movelist has changed
    }

    bool RepertoireViewModel::addNextMove(const Domain::Types::MoveData &move) {
        if (m_repertoire.data.addMoveFromNode(m_currentFEN, move.uci, move.stats)) {
            onPositionChanged(Utils::Chess::resultOfMove(m_currentFEN, move.uci));
            emit moveClicked(move.uci);
            return true;
        }
        return false;
    }

    bool RepertoireViewModel::removeMove(const Domain::Types::MoveData &move) {
        const auto current_node = m_repertoire.data.getNode(m_currentFEN);
        const int starting_edge_count = current_node->edgeCount();
        if (current_node->findMove(move.uci)) {
            std::erase_if(current_node->edges,
                          [&](const Domain::Types::MoveEdge &e) { return e.uci == move.uci; });
        }
        const int post_edge_count = current_node->edgeCount();
        if (starting_edge_count == post_edge_count) return false;
        if (starting_edge_count - 1 == post_edge_count) {
            onPositionChanged(m_currentFEN);
            return true;
        }
        std::cout << "RepertoireViewModel::removeMove was supposed to remove 1 move - " << starting_edge_count -
                post_edge_count << " Moves removed";
        return false;
    }

    void RepertoireViewModel::onPositionChanged(const Domain::Types::FEN &fen) {
        m_currentFEN = fen;
        QList<Domain::Types::MoveData> move_data_list{};
        const Domain::Types::PositionNode *node = m_repertoire.data.getNode({fen});
        if (!node) return;
        move_data_list.reserve(node->edgeCount());
        for (const auto &move_edge: node->edges) {
            Domain::Types::MoveData move_data{};
            move_data.uci = move_edge.uci;
            move_data.stats = m_repertoire.data.getNode(move_edge.target)->stats;
            move_data_list.append(move_data);
        }
        emit moveListChanged(move_data_list);
    }
}
