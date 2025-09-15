#ifndef _LIST_PAGE_H
#define _LIST_PAGE_H


namespace common { class WidgetList; } 

typedef QWidget typedef54;
class ListPage : public typedef54 {
  Q_OBJECT
  public:
    explicit ListPage(QWidget * parent = nullptr);

    // Methods to update UI state
    void updateRepertoireList(const QStringList & reps);

  signals:    // Events from user interactions
    void repertoireSelected(int _t1);

    void createRequested();

    void deleteRequested(QString _t1);

    void editRequested(QString _t1);

    void studyRequested(QString _t1);


  private:
    void initLayout();

    void initConnections();

    common::WidgetList * m_widget_list;

    QWidget * m_container;

    QPushButton * m_create_rep_btn;

};
#endif
