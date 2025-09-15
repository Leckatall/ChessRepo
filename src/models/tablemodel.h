#ifndef _TABLEMODEL_H
#define _TABLEMODEL_H


typedef QAbstractTableModel typedef32;
class TableModel : public typedef32 {
  Q_OBJECT
  public:
    inline explicit TableModel(QStringList headers, QObject * parent = nullptr, const Qt::Orientation & orientation = Qt::Horizontal) : QAbstractTableModel(parent),
              m_headers(std::move(headers)),
              m_orientation(orientation) {
        };

    inline void put_data(const QList<QMap<QString, QVariant> > & data, int role = Qt::EditRole) {
            beginResetModel();
            m_data = data;
            endResetModel();
            emit dataChanged(createIndex(0, 0),
                             createIndex(rowCount() - 1, columnCount() - 1),
                             {role});
        };

    inline void clear_data(int role = Qt::EditRole) {
            beginResetModel();
            m_data.clear();
            endResetModel();
            emit dataChanged(createIndex(0, 0),
                             createIndex(rowCount() - 1, columnCount() - 1),
                             {role});
        };

    inline constexpr Qt::Orientation get_orientation() const { return m_orientation; };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    int columnCount(const QModelIndex & parent = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

    QVariant get_cell(int row, const QString & column) const;

    QVariant get_cell(const QString & column, int row) const;

    void add_row(const QMap<QString, QVariant> & row);


  private:
    QStringList m_headers;

    Qt::Orientation m_orientation;

    QList<QMap<QString, QVariant> > m_data;

};
#endif
