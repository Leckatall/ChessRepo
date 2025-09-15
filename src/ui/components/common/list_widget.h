#ifndef COMMON_LIST_WIDGET_H
#define COMMON_LIST_WIDGET_H


namespace common {

typedef QScrollArea typedef45;
class WidgetList : public typedef45 {
  public:
    explicit WidgetList(QWidget * parent);

    void add_widget(QWidget * widget) const;

    void clear_widgets() const;


  protected:
    QWidget * m_container;

    QVBoxLayout * m_layout;

};

} // namespace common
#endif
