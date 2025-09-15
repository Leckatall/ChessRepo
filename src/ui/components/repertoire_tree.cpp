//
// Created by Lecka on 13/06/2025.
//

#include "repertoire_tree.h"

RepertoireTree::RepertoireTree(QWidget *parent)
    : QWidget(parent),
      m_tree_model(new RepoTreeModel),
      m_tree_view(new QTreeView(this)) {
    m_tree_view->setModel(m_tree_model);
    m_tree_view->setHeaderHidden(false);  // Make sure headers are visible
    m_tree_view->setRootIsDecorated(true);  // Show expand/collapse controls

}

void RepertoireTree::set_repertoire(const Models::Repertoire &repertoire) const {
    m_tree_model->set_repertoire(repertoire);
    qDebug() << "Model rows:" << m_tree_model->rowCount(QModelIndex());
}

void RepertoireTree::treeViewClicked(const QModelIndex &index) {

}
