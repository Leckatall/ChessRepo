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

#include "models/datatypes.h"


class RepertoireListPage : public QWidget {
    Q_OBJECT

public:
    explicit RepertoireListPage(QWidget *parent = nullptr);

    // Methods to update UI state
    void showRepertoireList(QStringList reps) const;

signals:
    // Events from user interactions
    void repertoireSelected(int id);

    void createRequested();

    void deleteRequested(int id);

private:
    QWidget *m_container;
    QVBoxLayout m_layout;

    QScrollArea m_scrollArea;
    QPushButton m_createButton;

    // Other UI elements
};


#endif //REPOTOIRELIST_PAGE_H
