//
// Created by Lecka on 11/06/2025.
//

#ifndef REPOCARD_H
#define REPOCARD_H
#include <QWidget>

#include "models/datatypes.h"


class RepoCard : public QWidget {
    Q_OBJECT

public:
    explicit RepoCard(QString repotoire_name, QWidget *parent = nullptr);

signals:
    void editClicked(Models::OpeningRepertoire m_rep);

    void studyClicked(Models::OpeningRepertoire m_rep);

    void deleteClicked(Models::OpeningRepertoire m_rep);

private:
    const QString m_rep;
};


#endif //REPOCARD_H
