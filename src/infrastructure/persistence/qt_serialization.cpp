//
// Created by Lecka on 20/09/2025.
//

#include "qt_serialization.h"

#include <qdatetime.h>

#include "repertoire/repertoire.h"
#include <qchronotimer.h>

#define IMPLEMENT_QT_SERIALIZATION(Type, name) \
template<> \
QDataStream& Serializer<Type>::serialize(QDataStream& stream, const Type& name)

#define IMPLEMENT_QT_DESERIALIZATION(Type, name) \
template<> \
QDataStream& Serializer<Type>::deserialize(QDataStream& stream, Type& name)

#define IMPLEMENT_QT_CONTAINER_SERIALIZATION(ContainerType, ValueType) \
template<> \
QDataStream &operator<<(QDataStream &stream, const ContainerType<ValueType> &container) { \
    stream << static_cast<quint32>(container.size()); \
    for (const auto &item : container) { \
        stream << item; \
    } \
    return stream; \
} \
template<> \
QDataStream &operator>>(QDataStream &stream, ContainerType<ValueType> &container) { \
    quint32 size; \
    stream >> size; \
    container.clear(); \
    container.reserve(size); \
    for (quint32 i = 0; i < size; ++i) { \
        ValueType item; \
        stream >> item; \
        container.append(item); \
    } \
    return stream; \
}


using namespace Domain::Types;

namespace Infrastructure::Features::Persistence {
    template<typename T>
    QDataStream &Serializer<T>::
    serialize(QDataStream &stream, const T &value) {
        static_assert(sizeof(T) == 0, "Serialization not implemented for this type");
        return stream;
    }

    template<typename T>
    QDataStream &Serializer<T>::deserialize(QDataStream &stream, T &obj) {
        static_assert(sizeof(T) == 0, "Deserialization not implemented for this type");
        return stream;
    }

    IMPLEMENT_QT_SERIALIZATION(Repertoire::Header, header) {
        stream << QString::fromStdString(header.name)
                << static_cast<qint8>(header.forWhite)
                << QString::fromStdString(header.description)
                << QString::fromStdString(header.author)
                << QDateTime::fromStdTimePoint(header.createdAt);

        return stream;
    }

    IMPLEMENT_QT_DESERIALIZATION(Repertoire::Header, header) {
        QString name, description, author;
        QDateTime createdAt;
        qint8 forWhite;
        stream >> name >> forWhite >> description >> author >> createdAt;
        header.name = name.toStdString();
        header.forWhite = forWhite != 0;
        header.description = description.toStdString();
        header.author = author.toStdString();
        header.createdAt = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>(std::chrono::sys_seconds::duration{createdAt.toSecsSinceEpoch()});
        return stream;
    }

    IMPLEMENT_QT_SERIALIZATION(PositionStats, stats) {
        stream << stats.games
                << stats.white_wins
                << stats.draws
                << stats.black_wins;
        return stream;
    }

    IMPLEMENT_QT_DESERIALIZATION(PositionStats, stats) {
        stream >> stats.games >> stats.white_wins >> stats.draws >> stats.black_wins;
        return stream;
    }

    IMPLEMENT_QT_SERIALIZATION(MoveEdge, move_edge) {
        stream << QString::fromStdString(move_edge.uci)
                << QString::fromStdString(move_edge.target.fen())
                << QString::fromStdString(move_edge.comment ? move_edge.comment.value() : "");
        return stream;
    }

    IMPLEMENT_QT_DESERIALIZATION(MoveEdge, move_edge) {
        QString uci, target_fen, comment;
        stream >> uci >> target_fen >> comment;
        move_edge.uci = UCIMove(uci.toStdString());
        move_edge.target = PositionKey(target_fen.toStdString());
        move_edge.comment = comment.toStdString();
        return stream;
    }

    IMPLEMENT_QT_CONTAINER_SERIALIZATION(QVector, MoveEdge)

    IMPLEMENT_QT_SERIALIZATION(PositionNode, node) {
        QList<MoveEdge> q_edges;
        q_edges.reserve(node.edges.size());
        for (const auto &edge: node.edges) {
            q_edges.append(edge);
        }
        stream << QString::fromStdString(node.getFen())
                << node.stats
                << q_edges;
        return stream;
    }

    IMPLEMENT_QT_DESERIALIZATION(PositionNode, node) {
        QString fen;
        PositionStats stats;
        QList<MoveEdge> qt_edges;
        stream >> fen >> stats >> qt_edges;
        node.key = PositionKey(fen.toStdString());
        node.stats = stats;
        node.edges.clear();
        node.edges.reserve(qt_edges.size());
        return stream;
    }

    IMPLEMENT_QT_CONTAINER_SERIALIZATION(QVector, PositionNode)

    IMPLEMENT_QT_SERIALIZATION(PositionGraph, graph) {
        QList<PositionNode> q_nodes;
        q_nodes.reserve(graph.nodeCount());
        for (const auto &node: graph.getNodes()) {
            q_nodes.append(node);
        }
        stream << q_nodes
                << QString::fromStdString(graph.getRootKey().fen());
        return stream;
    }

    IMPLEMENT_QT_DESERIALIZATION(PositionGraph, graph) {
        QList<PositionNode> nodes;
        QString root_fen;
        stream >> nodes >> root_fen;
        graph = PositionGraph(PositionKey(root_fen.toStdString()));
        for (const auto &node: nodes) {
            graph.addNode(node);
        }
        return stream;
    }

    IMPLEMENT_QT_SERIALIZATION(Repertoire::RepertoireData, repertoire_data) {
        stream << repertoire_data.header
                << repertoire_data.data;
        return stream;
    }

    IMPLEMENT_QT_DESERIALIZATION(Repertoire::RepertoireData, repertoire_data) {
        stream >> repertoire_data.header >> repertoire_data.data;
        return stream;
    }
}
