//
// Created by Lecka on 13/06/2025.
//

#ifndef EDIT_PAGE_H
#define EDIT_PAGE_H
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "moves_deck.h"
#include "controllers/boardcontroller.h"
#include "controllers/board_controller.h"
#include "controllers/explorer_controller.h"
#include "controllers/repertoire_viewer_controller.h"
#include "models/datatypes.h"
#include "ui/components/repertoire_tree.h"


class EditPage : public QWidget {
    Q_OBJECT

public:
    struct Components {
        chessboard::View* boardView;
        explorer::View* explorerView;
        repertoire_viewer::View* repView;
    };
    explicit EditPage(const Components& components, QWidget *parent = nullptr);

    void set_repertoire(const Models::Repertoire &repertoire) const;

    Models::Repertoire get_repertoire() { return m_current_repertoire; }

    void updateExplorer();

signals:
    void saveRequested();

    void addCurrentLine(QString comment);

    void moveAdded(const Models::FEN &fromPos, const Models::UCIMove &move);

    void moveDeleted(const Models::FEN &position);

    void commentUpdated(const Models::FEN &position, const QString &comment);

    void routeToListRequested();

    void explorerUpdateRequested(const Models::FEN &position);

private:
    void initLayout();

    void initConnections();

    QFrame *m_side_panel;
    // RepertoireTree *m_rep_tree;
    MovesDeck *m_moves_deck;

    QLineEdit *m_rep_name_edit;
    QTextEdit *m_comment_edit;

    QPushButton *m_delete_line_btn;
    QPushButton *m_save_line_btn;

    QPushButton *m_back_btn;

    Models::Repertoire m_current_repertoire;
};


#endif //EDIT_PAGE_H
