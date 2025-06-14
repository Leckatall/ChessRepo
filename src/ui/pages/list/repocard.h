//
// Created by Lecka on 11/06/2025.
//

#ifndef REPOCARD_H
#define REPOCARD_H
#include <QFrame>
#include <QWidget>

#include "models/datatypes.h"


class RepoCard : public QFrame {
    Q_OBJECT

public:
    explicit RepoCard(QString repotoire_name, QWidget *parent = nullptr);

signals:
    void editClicked(QString rep_name);

    void studyClicked(QString rep_name);

    void deleteClicked(QString rep_name);

private:
    const QString m_rep;
};


#endif //REPOCARD_H
