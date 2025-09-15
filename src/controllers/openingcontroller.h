#ifndef _OPENINGCONTROLLER_H
#define _OPENINGCONTROLLER_H


#include "Controller.h"
#include "repertoire_service.h"
#include "repertoire.h"

namespace Models { class FEN; } 

class OpeningController : public typedef27 {
  Q_OBJECT
  public:
    // TODO: Add lines to currently selected openers
    // TODO: Modal popup if there are unsaved changes
    // TODO: Display info within selected repo well
    // TODO: responses for fen
    // TODO: L8r add repo evaluator (coverage, strength, soundness)
    explicit OpeningController(QWidget * parent = nullptr);

    QWidget * view() const;

    QList<Models::UCIMove> responses_for_pos(const Models::FEN & pos);

  public slots:    void annotateForPosition(Models::FEN pos);

    bool createRepo();

  signals:    void boardChanged(const QString & _t1);

    void openerChaned();

  private slots:
  private:
    void saveRepo();

    void selectedOpenerChanged(int new_index);

    static QList<QString> getOpeners();

    void initUI();

    void initConnections();

    void update_combo_box();

    QFrame * m_container;

    QGridLayout m_layout;

    QComboBox m_opener_select;

    QPushButton m_load_opener_btn;

    QPushButton m_save_opener_btn;

    QPushButton m_add_line_btn;

    RepertoireService m_repo_service;

    QString m_add_opener_selection=  "Add New Opener...";

    QStringList m_openers;

    Models::Repertoire m_current_repo {};

};
#endif
