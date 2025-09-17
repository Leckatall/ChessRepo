//
// Created by Lecka on 14/06/2025.
//

#ifndef EXPLORER_VIEW_H
#define EXPLORER_VIEW_H
#include <QLabel>
#include <qtmetamacros.h>
#include <QWidget>

#include "explorer_tblview.h"
#include "../../../presentation/models/explorer_tblmodel.h"

namespace explorer {
    class View : public QWidget {
        Q_OBJECT

    public:
        explicit View(QWidget *parent = nullptr);

        void setTblModel(TblModel *model) const { m_tblView->setModel(model); }

        void initTblUi() const { m_tblView->initUI(); }

    signals:
        void moveIndexClicked(const QModelIndex &proxy_index);

    public slots:
        void updatePositionLabel(const QString &position_data_str) const;

    private:
        void initConnections();

        TblView *m_tblView;
        QLabel *m_current_pos_label;
    };
}

#endif //EXPLORER_VIEW_H
