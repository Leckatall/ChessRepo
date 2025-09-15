//
// Created by Lecka on 13/06/2025.
//

#ifndef REPERTOIRETREE_H
#define REPERTOIRETREE_H
#include <QTreeView>
#include <QWidget>

#include "models/repertoires/repotreemodel.h"


class RepertoireTree : public QWidget {
Q_OBJECT
public:
    explicit RepertoireTree(QWidget *parent = nullptr);

    void set_repertoire(const Models::Repertoire &repertoire) const;

signals:
    void moveClicked(Models::Move);

    void moveHovered(Models::Move);
private slots:
    void treeViewClicked(const QModelIndex& index);

private:
    RepoTreeModel* m_tree_model;
    QTreeView* m_tree_view;
};



#endif //REPERTOIRETREE_H
