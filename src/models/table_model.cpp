//
// Created by Lecka on 05/03/2025.
//


#include "Components/tablemodel.h"
#include <algorithm>


QVariant TableModel::get_cell(const int row, const std::string& column) const {
    if (row >= 0 && row < static_cast<int>(_data.size())) {
        if (auto it = _data[row].find(column); it != _data[row].end()) {
            return it->second;
        }
    }
    return {};
}

QVariant TableModel::get_cell(const std::string& column, const int row) const {
    return get_cell(row, column);
}



void TableModel::add_row(const std::map<std::string, QVariant>& row) {
    _data.push_back(row);
}

int TableModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    if (orientation == Qt::Horizontal) {
        return std::ranges::size(_data);
    }
    if (orientation == Qt::Vertical) {
        return std::ranges::size(headers);
    }
    qDebug() << "Unknown Orientation";
    return 0;
}

int TableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    if (orientation == Qt::Horizontal) {
        return std::ranges::size(headers);
    } else if (orientation == Qt::Vertical) {
        return std::ranges::size(_data);
    }
    qDebug() << "Unknown Orientation";
    return 0;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (orientation == Qt::Horizontal) {
            auto it = _data[index.row()].find(headers[index.column()]);
            return it != _data[index.row()].end() ? it->second : QVariant();
        }
        if (orientation == Qt::Vertical) {
            auto it = _data[index.column()].find(headers[index.row()]);
            return it != _data[index.column()].end() ? it->second : QVariant();
        }
        qDebug() << "Unknown Orientation";
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orient, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orient != orientation) {
        return QString("Row %1").arg(section);
    }

    return QString::fromStdString(headers[section]);
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::EditRole) {
        if (orientation == Qt::Horizontal) {
            _data[index.row()][headers[index.column()]] = value;
        } else if (orientation == Qt::Vertical) {
            _data[index.column()][headers[index.row()]] = value;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void TableModel::update_data(const std::vector<std::map<std::string, QVariant>>& data) {
    beginResetModel();
    _data = data;
    endResetModel();
}

QModelIndex TableModel::get_row_by_id(const QVariant& source, const QVariant& listing_id) const {
    for (auto rows = std::views::iota(0, rowCount()); const int row : rows) {
        QModelIndex source_index = index(row, 0);
        QModelIndex id_index = index(row, 1);

        if (data(id_index) == listing_id) {
            if (data(source_index) == source) {
                return source_index;
            }
        }
    }
    return QModelIndex();
}
