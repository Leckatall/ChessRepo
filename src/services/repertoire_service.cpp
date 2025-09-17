//
// Created by Lecka on 06/04/2025.
//

#include "repertoire_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QDir"
#include "models/datatypes/position.h"


Models::Repertoire RepertoireService::read_repertoire_file(const QString &name) {
    // Temporary stub during refactor: return an empty repertoire with only header filled.
    Models::Repertoire rep;
    rep.header.name = name;
    // Return without caching to avoid copying a non-copyable type during refactor
    return rep;
}