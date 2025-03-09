//
// Created by Lecka on 09/03/2025.
//

#include "openingbook.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

bool OpeningBook::save(QString filepath) {
    QDomDocument doc;
    QDomElement root = doc.createElement("Book");
    root.setAttribute("title", title);
    root.setAttribute("forColor", forColor);
    root.setAttribute("description", description);

    for (auto it = states.begin(); it != states.end(); ++it) {
        const QString& boardHash = it.key();
        const BoardState& state = it.value();
        QDomElement stateElement = doc.createElement("State");
        stateElement.setAttribute("boardHash", boardHash);
        stateElement.setAttribute("comment", state.comment);

        for (const Move& move : state.moves) {
            QDomElement moveElement = doc.createElement("Move");
            moveElement.setAttribute("move", move.move);
            moveElement.setAttribute("resultingBoardHash", move.resultHash);
            stateElement.appendChild(moveElement);
        }
        root.appendChild(stateElement);
    }

    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
    return true;
}



