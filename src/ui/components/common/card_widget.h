#ifndef COMMON_CARD_WIDGET_H
#define COMMON_CARD_WIDGET_H


namespace common {

typedef QFrame typedef44;
class CardWidget : public typedef44 {
  Q_OBJECT
  public:
    explicit CardWidget(const QString & title = "", QWidget * parent = nullptr);

  signals:    void clicked();


  protected:
    void mousePressEvent(QMouseEvent * event) override;

    QLabel * m_title_lbl;

    QGridLayout * m_content_layout;


  private:
    void initStyle();

};

} // namespace common
#endif
