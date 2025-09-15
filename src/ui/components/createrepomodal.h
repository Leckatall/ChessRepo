#ifndef _CREATEREPOMODAL_H
#define _CREATEREPOMODAL_H


namespace Models { struct Repertoire; } 

typedef QDialog typedef38;
class CreateRepoModal : public typedef38 {
  Q_OBJECT
  public:
    // TODO: Don't allow creation of repos with names that already exist
    explicit CreateRepoModal(QWidget * parent = nullptr);

    Models::Repertoire getRepertoire() const;

  private slots:
  private:
    void validateForm() const;

    void initUI();

    QFormLayout m_layout;

    QLineEdit m_name_edit;

    QTextEdit m_desc_edit;

    QLineEdit m_auth_edit;

    QCheckBox m_for_white_check_box;

    QDialogButtonBox m_button_box;

};
#endif
