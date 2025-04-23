//
// Created by Lecka on 22/04/2025.
//

#ifndef REPOTREEMODEL_H
#define REPOTREEMODEL_H
#include <qabstractitemmodel.h>

#include "models/datatypes.h"


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

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Helper Methods
    void set_repertoire(const Models::OpeningRepertoire &rep);
    [[nodiscard]] Models::FEN positionAt(const QModelIndex& index) const;

private:
    struct TreeNode {
        Models::FEN position;
        TreeNode *parent{nullptr};
        QVector<TreeNode *> children;
        const Models::OpeningPosition *data{nullptr}; // Pointer to position data in repertoire

        explicit TreeNode(Models::FEN pos, TreeNode *p = nullptr)
            : position(std::move(pos)), parent(p) {
        }

        ~TreeNode() {
            qDeleteAll(children);
        }
    };

    Models::OpeningRepertoire m_repertoire;
    TreeNode *m_root{nullptr};

    void buildTree();

    void clearTree();

    [[nodiscard]] TreeNode *getNode(const QModelIndex &index) const;

    static const QMap<Column, QString> COLUMN_NAMES;
};


#endif //REPOTREEMODEL_H
