//
// Created by Lecka on 22/04/2025.
//

#include "repotreemodel.h"
#include "QMetaEnum"

const QMap<RepoTreeModel::Column, QString> RepoTreeModel::COLUMN_NAMES = {
    {MoveSAN, "Move"},
    {Comment, "Comment"}
};

QModelIndex RepoTreeModel::index(const int row, const int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return {};

    TreeNode *parentNode = parent.isValid() ? getNode(parent) : m_root;
    if (!parentNode) return {};

    if (row < parentNode->children.size())
        return createIndex(row, column, &parentNode->children[row]);

    return {};
}

QModelIndex RepoTreeModel::parent(const QModelIndex &child) const {
    if (!child.isValid())
        return {};

    TreeNode* childNode = getNode(child);
    if (!childNode || !childNode->parent)
        return {};

    TreeNode* parentNode = childNode->parent;
    if (parentNode == m_root)
        return {};

    // Find row of parent
    TreeNode* grandparent = parentNode->parent;
    if (!grandparent)
        return {};

    const int row = grandparent->children.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

int RepoTreeModel::rowCount(const QModelIndex &parent) const {
    if (parent.column() > 0)
        return 0;

    TreeNode* parentNode = parent.isValid() ? getNode(parent) : m_root;
    return parentNode ? parentNode->children.size() : 0;
}

int RepoTreeModel::columnCount(const QModelIndex &parent) const {
    return ColumnCount;
}

QVariant RepoTreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    TreeNode* node = getNode(index);
    if (!node || !node->data)
        return {};

    const Models::OpeningPosition& pos = *node->data;

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case MoveSAN:
                return pos.recommendedMove;
            case Comment:
                return pos.comment;
            default:
                return {};
        }
    }
    return {};
}

QVariant RepoTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation != Qt::Horizontal) {
        return {};
    }
    if(section < ColumnCount) {
        return COLUMN_NAMES[static_cast<Column>(section)];
    }
    return {};
}

void RepoTreeModel::set_repertoire(const Models::OpeningRepertoire &rep) {
    beginResetModel();
    m_repertoire = rep;
    buildTree();
    endResetModel();
}

void RepoTreeModel::buildTree() {
    clearTree();
    m_root = new TreeNode(Models::FEN::startingPosition());

    // Build tree structure
    QMap<Models::FEN, TreeNode *> nodeMap;
    nodeMap[m_root->position] = m_root;

    // First pass: create nodes and establish parent-child relationships
    for (auto it = m_repertoire.positions.constBegin();
         it != m_repertoire.positions.constEnd(); ++it) {
        const Models::OpeningPosition &pos = it.value();
        TreeNode *node = nodeMap.value(it.key(), nullptr);

        if (!node) {
            node = new TreeNode(it.key());
            nodeMap[it.key()] = node;
        }

        node->data = &pos;

        // Create child nodes for all responses
        for (auto respIt = pos.responses.constBegin();
             respIt != pos.responses.constEnd(); ++respIt) {
            const Models::FEN &childFen = respIt.value();
            TreeNode *childNode = nodeMap.value(childFen, nullptr);

            if (!childNode) {
                childNode = new TreeNode(childFen, node);
                nodeMap[childFen] = childNode;
            } else {
                childNode->parent = node;
            }

            node->children.append(childNode);
        }
    }

    // Second pass: remove orphaned nodes (except root)
    for (auto it = nodeMap.begin(); it != nodeMap.end();) {
        if (it.value() != m_root && !it.value()->parent) {
            delete it.value();
            it = nodeMap.erase(it);
        } else {
            ++it;
        }
    }
}

void RepoTreeModel::clearTree() {
    delete m_root;
    m_root = nullptr;
}

RepoTreeModel::TreeNode * RepoTreeModel::getNode(const QModelIndex &index) const {
    return static_cast<TreeNode*>(index.internalPointer());
}
