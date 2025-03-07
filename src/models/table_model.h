//
// Created by Lecka on 05/03/2025.
//

#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <ranges>

class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    template<std::ranges::range R>
    requires std::convertible_to<std::ranges::range_value_t<R>, std::string>
    explicit TableModel(R&& headers,
                        QObject* parent = nullptr,
                        Qt::Orientation orientation = Qt::Horizontal)
        : headers(std::ranges::begin(headers), std::ranges::end(headers)),
          orientation(orientation)
    {}

    template<std::ranges::viewable_range R>
    requires std::is_same_v<std::ranges::range_value_t<R>, std::map<std::string, QVariant>>
    void update_data(R&& data) {
        beginResetModel();
        _data = std::forward<R>(data);
        endResetModel();
    }

    // Constexpr and nodiscard specifiers
    [[nodiscard]] constexpr Qt::Orientation get_orientation() const { return orientation; }


    [[nodiscard]] int rowCount(const QModelIndex &parent=QModelIndex()) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent=QModelIndex()) const override;

    [[nodiscard]] Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;


    [[nodiscard]] QVariant get_cell(int row, const std::string &column) const;
    [[nodiscard]] QVariant get_cell(const std::string &column, int row) const;

    void add_row(const std::map<std::string, QVariant> &row);



    [[nodiscard]] QModelIndex get_row_by_id(const QVariant &source, const QVariant &listing_id) const;

private:
    std::vector<std::string> headers;
    Qt::Orientation orientation;
    std::vector<std::map<std::string, QVariant> > _data;
};

#endif //TABLEMODEL_H
