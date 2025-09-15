#ifndef EXPLORER_EXPLORER_VIEW_H
#define EXPLORER_EXPLORER_VIEW_H


namespace explorer { class TblModel; } 
namespace explorer { class TblView; } 

namespace explorer {

typedef QWidget typedef48;
class View : public typedef48 {
  Q_OBJECT
  public:
    explicit View(QWidget * parent = nullptr);

    inline void setTblModel(TblModel * model) const { m_tblView->setModel(model); };

    inline void initTblUi() const { m_tblView->initUI(); };

  signals:    void moveIndexClicked(const QModelIndex & _t1);

  public slots:    void updatePositionLabel(const QString & position_data_str) const;


  private:
    void initConnections();

    TblView * m_tblView;

    QLabel * m_current_pos_label;

};

} // namespace explorer
#endif
