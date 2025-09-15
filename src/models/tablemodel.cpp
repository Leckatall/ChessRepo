
#include "tablemodel.h"

int TableModel::rowCount() const {

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

int TableModel::columnCount() const {

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

QVariant TableModel::data() const {

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

bool TableModel::setData() {

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

void TableModel::add_row() {

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(row);
    endInsertRows();
    emit dataChanged(createIndex(rowCount() - 1, 0),
        createIndex(rowCount() - 1, columnCount() - 1));
}

