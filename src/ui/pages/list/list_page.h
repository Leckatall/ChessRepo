//
// Created by Lecka on 11/06/2025.
//

#ifndef REPOTOIRELIST_PAGE_H
#define REPOTOIRELIST_PAGE_H
#include <qboxlayout.h>
#include <QPushButton>
#include <qtmetamacros.h>
#include <QWidget>
#include <QScrollArea>

#include "ui/components/common/list_widget.h"


class ListPage : public QWidget {
    Q_OBJECT

public:
    explicit ListPage(QWidget *parent = nullptr);

    // Methods to update UI state
    void updateRepertoireList(const QStringList &reps);

signals:
    // Events from user interactions
    void repertoireSelected(int id);

    void createRequested();

    void deleteRequested(QString rep_name);

    void editRequested(QString rep_name);

    void studyRequested(QString rep_name);

private:
    void initLayout();

    void initConnections();

    common::WidgetList* m_widget_list;
    QWidget *m_container;
    QPushButton *m_create_rep_btn;
};


#endif //REPOTOIRELIST_PAGE_H
