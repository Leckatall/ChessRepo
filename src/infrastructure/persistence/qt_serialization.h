//
// Created by Lecka on 20/09/2025.
//

#ifndef CHESSREPO_QT_SERIALIZATION_H
#define CHESSREPO_QT_SERIALIZATION_H
#include <qdatastream.h>

#include "types/position/position_graph.h"

#define DECLARE_QT_SERIALIZABLE(Type) \
template<> \
QDataStream& Serializer<Type>::serialize(QDataStream& stream, const Type& value); \
template<> \
QDataStream& Serializer<Type>::deserialize(QDataStream& stream, Type& obj);

namespace Domain::Types {
    struct MoveEdge;
    struct PositionStats;
    struct PositionNode;

    namespace Repertoire {
        struct Header;
        struct RepertoireData;
    }
}

namespace Infrastructure::Features::Persistence {
    template<typename T>
    class Serializer {
    public:
        static QDataStream &serialize(QDataStream &stream, const T &value);

        static QDataStream &deserialize(QDataStream &stream, T &obj);
    };

    DECLARE_QT_SERIALIZABLE(Domain::Types::Repertoire::Header)

    DECLARE_QT_SERIALIZABLE(Domain::Types::PositionStats)

    DECLARE_QT_SERIALIZABLE(Domain::Types::MoveEdge)

    DECLARE_QT_SERIALIZABLE(Domain::Types::PositionNode)

    DECLARE_QT_SERIALIZABLE(Domain::Types::PositionGraph)

    DECLARE_QT_SERIALIZABLE(Domain::Types::Repertoire::RepertoireData)


    template<typename T>
    QDataStream &operator<<(QDataStream &stream, const T &obj) {
        return Serializer<T>::serialize(stream, obj);
    }

    template<typename T>
    QDataStream &operator>>(QDataStream &stream, T &obj) {
        return Serializer<T>::deserialize(stream, obj);
    }

    // template<typename T>
    // QDataStream &operator<<(QDataStream &stream, const QVector<T> &vector) {
    //     stream << static_cast<quint32>(vector.size());
    //     for (const auto &item: vector) {
    //         stream << item; // This will call your Serializer<T>::serialize
    //     }
    //     return stream;
    // }
    //
    // template<typename T>
    // QDataStream &operator>>(QDataStream &stream, QVector<T> &vector) {
    //     quint32 size;
    //     stream >> size;
    //     vector.clear();
    //     vector.reserve(size);
    //     for (quint32 i = 0; i < size; ++i) {
    //         T item;
    //         stream >> item; // This will call your Serializer<T>::deserialize
    //         vector.append(item);
    //     }
    //     return stream;
    // }
}


#endif //CHESSREPO_QT_SERIALIZATION_H
