// //
// // Created by Lecka on 09/03/2025.
// //
//
// #ifndef INFOFRAME_H
// #define INFOFRAME_H
//
// #include <QFrame>
// #include <QComboBox>
//
// #include "controllers/explorercontroller.h"
//
//
// class InfoFrame : public QFrame {
//     Q_OBJECT
//
// public:
//     explicit InfoFrame(QWidget *parent = nullptr);
//
//     void setContents(const QString &content);
//
// private:
//     void initUI();
//
//     void initLayout();
//
//     QComboBox *contentsSelect;
//     QFrame *contentFrame;
//     QMap<QString, ContentController *> m_content_list = {
//         {"Nothing", new ContentController(this)},
//         {"Explorer", new ExplorerController(this)}
//     };
// };
//
//
// #endif //INFOFRAME_H
