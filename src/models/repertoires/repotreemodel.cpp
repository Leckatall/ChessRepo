
#include "repotreemodel.h"
#include "chess_primitives.h"
#include "move.h"
#include "position.h"

QModelIndex RepoTreeModel::parent() const {

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

int RepoTreeModel::rowCount() const {

    if (parent.column() > 0)
        return 0;

    TreeNode* parentNode = parent.isValid() ? getNode(parent) : m_root;
    return parentNode ? parentNode->children.size() : 0;
}

int RepoTreeModel::columnCount() const {

    return ColumnCount;
}

QVariant RepoTreeModel::data() const {

    if (!index.isValid())
        return {};

    TreeNode* node = getNode(index);
    if (!node)
        return {};

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case MoveSAN:
                return node->data.recommendedMove;
            case Comment:
                return node->data.comment;
            default:
                return {};
        }
    }
    return {};
}

QVariant RepoTreeModel::headerData() const {

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

// Helper Methods
void RepoTreeModel::set_repertoire() {

    beginResetModel();
    m_repertoire = rep;
    buildTree();
    endResetModel();
}

Models::FEN RepoTreeModel::positionAt() const {

    return Models::FEN::startingPosition();
}

Models::Move RepoTreeModel::moveAt() const {

    return {"e2e4", "nice type checking nerd"};
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

        node->data = pos;

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

TreeNode RepoTreeModel::getNode() const {

    return static_cast<TreeNode*>(index.internalPointer());
}

const QMap<RepoTreeModel::Column,QString> RepoTreeModel::COLUMN_NAMES= {
    {MoveSAN, "Move"},
    {Comment, "Comment"}
};

