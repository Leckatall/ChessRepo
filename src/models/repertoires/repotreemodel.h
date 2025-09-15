//
// Created by Lecka on 22/04/2025.
//

#ifndef REPOTREEMODEL_H
#define REPOTREEMODEL_H
#include <qabstractitemmodel.h>

#include "models/datatypes/chess_primitives.h"
#include "models/datatypes/move.h"
#include "models/datatypes/repertoire.h"


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
        : QAbstractItemModel(parent),
          m_root(new TreeNode(Models::FEN::startingPosition())) {
    }

    // Overrides
    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    [[nodiscard]] QModelIndex parent(const QModelIndex &child) const override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Helper Methods
    void set_repertoire(const Models::Repertoire &rep);
    [[nodiscard]] Models::FEN positionAt(const QModelIndex& index) const;
    [[nodiscard]] Models::Move moveAt(const QModelIndex& index) const;

private:
    Models::Repertoire m_repertoire;
    Models::Position *m_root{nullptr};

    void buildTree();

    void clearTree();

    [[nodiscard]] TreeNode *getNode(const QModelIndex &index) const;

    static const QMap<Column, QString> COLUMN_NAMES;
};


#endif //REPOTREEMODEL_H
