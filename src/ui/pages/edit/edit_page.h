#ifndef _EDIT_PAGE_H
#define _EDIT_PAGE_H


#include "repertoire.h"

namespace chessboard { class View; } 
namespace explorer { class View; } 
namespace repertoire_viewer { class View; } 
namespace Models { class FEN; } 
namespace Models { class UCIMove; } 
class MovesDeck;

typedef QWidget typedef52;
class EditPage : public typedef52 {
  Q_OBJECT
  public:
    struct Components {
        chessboard::View * boardView;

        explorer::View * explorerView;

        repertoire_viewer::View * repView;

    };
    
    explicit EditPage(const Components & components, QWidget * parent = nullptr);

    void set_repertoire(const Models::Repertoire & repertoire) const;

    inline Models::Repertoire get_repertoire() { return m_current_repertoire; };

    void updateExplorer();

  signals:    void saveRequested();

    void addCurrentLine(QString _t1 = "");

    void moveAdded(const Models::FEN & _t1, const Models::UCIMove & _t2);

    void moveDeleted(const Models::FEN & _t1);

    void commentUpdated(const Models::FEN & _t1, const QString & _t2);

    void routeToListRequested();

    void explorerUpdateRequested(const Models::FEN & _t1);


  private:
    void initLayout();

    void initConnections();

    QFrame * m_side_panel;

    // RepertoireTree *m_rep_tree;
    
    MovesDeck * m_moves_deck;

    QLineEdit * m_rep_name_edit;

    QTextEdit * m_comment_edit;

    QPushButton * m_delete_line_btn;

    QPushButton * m_save_line_btn;

    QPushButton * m_back_btn;

    Models::Repertoire m_current_repertoire;

};
#endif
