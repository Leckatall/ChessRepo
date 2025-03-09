//
// Created by Lecka on 09/03/2025.
//

#ifndef OPENINGMODEL_H
#define OPENINGMODEL_H
#include <QObject>
#include <QHash>

struct Move {
    QString move;
    QString resultHash;
};


struct BoardState {
    QString comment;
    QList<Move> moves;
};


class OpeningBook: public QObject {
Q_OBJECT
public:
    bool save(QString filepath);

    QString forColor;
    QString title;
    QString description;
    QHash<QString, BoardState> states;
};



#endif //OPENINGMODEL_H
