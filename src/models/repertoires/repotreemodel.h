#ifndef _REPOTREEMODEL_H
#define _REPOTREEMODEL_H


#include "repertoire.h"

namespace Models { class FEN; } 
namespace Models { struct Move; } 
namespace Models { struct Position; } 

typedef QAbstractItemModel typedef36;
class RepoTreeModel : public typedef36 {
  Q_OBJECT
  public:
    enum Column {
      MoveSAN =  0,
      Comment,
      ColumnCount
    };

    inline explicit RepoTreeModel(QObject * parent = nullptr) : QAbstractItemModel(parent),
              m_root(new TreeNode(Models::FEN::startingPosition())) {
        };

    // Overrides
    QModelIndex index(int row, int column, const QModelIndex & parent) const override;

    QModelIndex parent(const QModelIndex & child) const override;

    int rowCount(const QModelIndex & parent) const override;

    int columnCount(const QModelIndex & parent) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Helper Methods
    void set_repertoire(const Models::Repertoire & rep);

    Models::FEN positionAt(const QModelIndex & index) const;

    Models::Move moveAt(const QModelIndex & index) const;


  private:
    Models::Repertoire m_repertoire;

    Models::Position * m_root {nullptr};

    void buildTree();

    void clearTree();

    TreeNode * getNode(const QModelIndex & index) const;

    static const QMap<Column,QString> COLUMN_NAMES;

};
#endif
