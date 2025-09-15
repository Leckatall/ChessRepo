
#include "repertoire_tree.h"
#include "repertoire.h"
#include "move.h"
#include "repotreemodel.h"

RepertoireTree::RepertoireTree(QWidget * parent)
    : QWidget(parent),
      m_tree_model(new RepoTreeModel),
      m_tree_view(new QTreeView(this)) {

    m_tree_view->setModel(m_tree_model);
    m_tree_view->setHeaderHidden(false);  // Make sure headers are visible
    m_tree_view->setRootIsDecorated(true);  // Show expand/collapse controls

}

void RepertoireTree::set_repertoire() const {

    m_tree_model->set_repertoire(repertoire);
    qDebug() << "Model rows:" << m_tree_model->rowCount(QModelIndex());
}

// SIGNAL 0

void RepertoireTree::moveClicked(Models::Move _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1

void RepertoireTree::moveHovered(Models::Move _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

void RepertoireTree::treeViewClicked() {


}

