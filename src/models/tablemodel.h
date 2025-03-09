//
// Created by Lecka on 05/03/2025.
//

#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <QStringList>
#include <utility>

class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TableModel(QStringList headers,
                        QObject *parent = nullptr,
                        const Qt::Orientation &orientation = Qt::Horizontal)
        : QAbstractTableModel(parent),
          m_headers(std::move(headers)),
          m_orientation(orientation) {
    }

    void update_data(const QList<QMap<QString, QVariant> > &data, int role = Qt::EditRole) {
        beginResetModel();
        m_data = data;
        endResetModel();
        emit dataChanged(index(0,0),
            index(rowCount() - 1, columnCount() - 1),
            {role});
    }

    // Constexpr and nodiscard specifiers
    [[nodiscard]] constexpr Qt::Orientation get_orientation() const { return m_orientation; }


    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QVariant
    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;


    [[nodiscard]] QVariant get_cell(int row, const QString &column) const;

    [[nodiscard]] QVariant get_cell(const QString &column, int row) const;

    void add_row(const QMap<QString, QVariant> &row);

private:
    QStringList m_headers;
    Qt::Orientation m_orientation;
    QList<QMap<QString, QVariant> > m_data;
};

#endif //TABLEMODEL_H
