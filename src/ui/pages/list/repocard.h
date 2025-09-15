#ifndef _REPOCARD_H
#define _REPOCARD_H


#include "card_widget.h"

class RepoCard : public common::CardWidget {
  Q_OBJECT
  public:
    explicit RepoCard(QString repotoire_name, QWidget * parent = nullptr);

  signals:    void editClicked(QString _t1);

    void studyClicked(QString _t1);

    void deleteClicked(QString _t1);


  private:
    const QString m_rep;

};
#endif
