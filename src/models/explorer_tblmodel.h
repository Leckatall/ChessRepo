#ifndef EXPLORER_EXPLORER_TBLMODEL_H
#define EXPLORER_EXPLORER_TBLMODEL_H


#include "position.h"

namespace Models { struct MoveData; } 

namespace explorer {

typedef QAbstractTableModel typedef30;
class TblModel : public typedef30 {
  Q_OBJECT
  public:
    enum Column {
      MoveName =  0,
      Popularity,
      Winrates,
      Evaluation,
      ColumnCount
    };

    explicit TblModel(QObject * parent = nullptr, const Qt::Orientation & orientation = Qt::Horizontal);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int columnCount(const QModelIndex & parent = QModelIndex()) const override;

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    inline void put_data(const QList<Models::MoveData> & moves) {
                beginResetModel();
                m_moves = moves;
                endResetModel();
                emit dataChanged(createIndex(0, 0),
                                 createIndex(rowCount() - 1, columnCount() - 1));
            };

    inline void set_root_position(const Models::Position & root_position) {
                m_root_position = root_position;
            };

  public slots:    void handleClick(const QModelIndex & index);

  signals:    void moveClicked(const Models::MoveData & _t1);


  private:
    Qt::Orientation m_orientation;

    static const QMap<Column,QString> COLUMN_NAMES;

    QList<Models::MoveData> m_moves;

    Models::Position m_root_position;

};

} // namespace explorer
#endif
