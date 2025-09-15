#ifndef _REPERTOIRE_TREE_H
#define _REPERTOIRE_TREE_H


namespace Models { struct Repertoire; } 
namespace Models { struct Move; } 
class RepoTreeModel;

typedef QWidget typedef40;
class RepertoireTree : public typedef40 {
  Q_OBJECT
  public:
    explicit RepertoireTree(QWidget * parent = nullptr);

    void set_repertoire(const Models::Repertoire & repertoire) const;

  signals:    void moveClicked(Models::Move _t1);

    void moveHovered(Models::Move _t1);

  private slots:
  private:
    void treeViewClicked(const QModelIndex & index);

    RepoTreeModel * m_tree_model;

    QTreeView * m_tree_view;

};
#endif
