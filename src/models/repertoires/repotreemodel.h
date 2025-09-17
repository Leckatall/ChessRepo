//
// Created by Lecka on 22/04/2025.
//

#ifndef REPOTREEMODEL_H
#define REPOTREEMODEL_H
#include <qabstractitemmodel.h>

#include "models/datatypes/chess_primitives.h"
#include "models/datatypes/move.h"
#include "models/datatypes/repertoire_tree.h"

// Minimal stub implementation to keep build green during refactor
class RepoTreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    enum Column {
        MoveSAN = 0,
        Comment,
        ColumnCount
    };

    Q_ENUM(Column);

    explicit RepoTreeModel(QObject *parent = nullptr)
        : QAbstractItemModel(parent) {}

    // Overrides
    [[nodiscard]] QModelIndex index(int, int, const QModelIndex &) const override { return {}; }

    [[nodiscard]] QModelIndex parent(const QModelIndex &) const override { return {}; }

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override { Q_UNUSED(parent); return 0; }

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override { Q_UNUSED(parent); return ColumnCount; }

    [[nodiscard]] QVariant data(const QModelIndex &, int) const override { return {}; }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        Q_UNUSED(section); Q_UNUSED(orientation); Q_UNUSED(role); return {}; }

    // Helper Methods
    void set_repertoire(const Models::RepTree::RepertoireTree &/*rep*/) { /* no-op stub */ }
    [[nodiscard]] Models::FEN positionAt(const QModelIndex& /*index*/) const { return Models::FEN::startingPosition(); }
    [[nodiscard]] Models::Move moveAt(const QModelIndex& /*index*/) const { return {"e2e4", "e4"}; }
};

#endif //REPOTREEMODEL_H
