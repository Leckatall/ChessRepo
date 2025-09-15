
#include "explorer_tblmodel.h"
#include "move.h"

namespace explorer {

TblModel::TblModel(QObject * parent, const Qt::Orientation & orientation)
    : QAbstractTableModel(parent),
      m_orientation(orientation) {

}

QVariant TblModel::headerData() const {

    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation != m_orientation) {
        return QString("Row %1").arg(section);
    }
    if(section < ColumnCount) {
        return COLUMN_NAMES[static_cast<Column>(section)];
    }
    return {};
}

int TblModel::columnCount() const {

    if(parent.isValid())
        return 0;
    return ColumnCount;
}

int TblModel::rowCount() const {

    if(parent.isValid())
        return 0;
    return m_moves.size();
}

QVariant TblModel::data() const {

    if (!index.isValid() || index.row() >= m_moves.size()) {
        return {};
    }
    const Models::MoveData &move_data = m_moves[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (static_cast<Column>(index.column())) {
            case MoveName:
                return move_data.move.san;
            case Popularity:
                return Models::formatPercentage(static_cast<double>(move_data.position_data.games) / static_cast<double>(m_root_position.games));
            case Winrates:
                return {};
            case Evaluation:
                return 0;
            case ColumnCount:
                break;
        }
    } else if (role == Qt::UserRole) {
        if(static_cast<Column>(index.column()) == Winrates) {
            return QVariant::fromValue(move_data.position_data);
        }
    } else if (role == Qt::ToolTipRole) {
        if(static_cast<Column>(index.column()) == Winrates) {
            return move_data.position_data.toToolTip();
        }
    }else if (role == Qt::TextAlignmentRole )
        return Qt::AlignCenter;

    return {};

}

void TblModel::handleClick() {

    if (!index.isValid() || index.row() >= m_moves.size())
        return;

    emit moveClicked(m_moves[index.row()]);
}

// SIGNAL 0

void TblModel::moveClicked(const Models::MoveData & _t1) {

    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

const QMap<TblModel::Column,QString> TblModel::COLUMN_NAMES= {
    {MoveName, "Move"},
    {Popularity, "Popularity"},
    {Winrates, "Win Rates"},
    {Evaluation, "Evaluation"}
};


} // namespace explorer
