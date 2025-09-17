//
// Created by Lecka on 06/04/2025.
//

#ifndef OPENINGCONTROLLER_H
#define OPENINGCONTROLLER_H
#include <qboxlayout.h>
#include <QObject>
#include <QPushButton>
#include <QFrame>
#include <qitemselectionmodel.h>
#include <QComboBox>

#include "models/datatypes.h"
#include "../infrastructure/persistence/repertoire_service.h"


class OpeningController : public QObject {
    Q_OBJECT
    // TODO: Add lines to currently selected openers
    // TODO: Modal popup if there are unsaved changes
    // TODO: Display info within selected repo well
    // TODO: responses for fen
    // TODO: L8r add repo evaluator (coverage, strength, soundness)
public:
    explicit OpeningController(QWidget *parent = nullptr);

    [[nodiscard]] QWidget *view() const;

    QList<Models::UCIMove> responses_for_pos(const Models::FEN &pos);

public slots:
    void annotateForPosition(Models::FEN pos);

    bool createRepo();

signals:
    void boardChanged(const QString &fen);

    void openerChaned();

private slots:
    void saveRepo();

    void selectedOpenerChanged(int new_index);

    static QList<QString> getOpeners();

private:
    void initUI();

    void initConnections();

    void update_combo_box();

    QFrame *m_container;
    QGridLayout m_layout;
    QComboBox m_opener_select;
    QPushButton m_load_opener_btn;
    QPushButton m_save_opener_btn;
    QPushButton m_add_line_btn;


    RepertoireService m_repo_service;

    QString m_add_opener_selection = "Add New Opener...";
    QStringList m_openers;
    Models::Repertoire m_current_repo{};
};


#endif //OPENINGCONTROLLER_H
