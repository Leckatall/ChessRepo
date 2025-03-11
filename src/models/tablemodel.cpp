//
// Created by Lecka on 05/03/2025.
//


#include "tablemodel.h"
#include <algorithm>


QVariant TableModel::get_cell(const int row, const QString& column) const {
    if (row >= 0 && row < m_data.length()) {
        return m_data[row][column];
    }
    return {};
}

QVariant TableModel::get_cell(const QString& column, const int row) const {
    return get_cell(row, column);
}

void TableModel::add_row(const QMap<QString, QVariant>& row) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(row);
    endInsertRows();
    emit dataChanged(createIndex(rowCount() - 1, 0),
        createIndex(rowCount() - 1, columnCount() - 1));
}

int TableModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    if (m_orientation == Qt::Horizontal) {
        return m_data.length();
    }
    if (m_orientation == Qt::Vertical) {
        return m_headers.length();
    }
    qDebug() << "Unknown Orientation";
    return 0;
}

int TableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    if (m_orientation == Qt::Horizontal) {
        return m_headers.length();
    }
    if (m_orientation == Qt::Vertical) {
        return m_data.length();
    }
    qDebug() << "Unknown Orientation";
    return 0;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return {};
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (m_orientation == Qt::Horizontal) {
            return m_data[index.row()][m_headers[index.column()]];
        }
        if (m_orientation == Qt::Vertical) {
            return m_data[index.column()][m_headers[index.row()]];
        }
        qDebug() << "Unknown Orientation";
    }
    return {};
}

QVariant TableModel::headerData(int section, Qt::Orientation orient, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orient != m_orientation) {
        return QString("Row %1").arg(section);
    }

    return m_headers[section];
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::EditRole) {
        if (m_orientation == Qt::Horizontal) {
            m_data[index.row()][m_headers[index.column()]] = value;
        } else if (m_orientation == Qt::Vertical) {
            m_data[index.column()][m_headers[index.row()]] = value;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}