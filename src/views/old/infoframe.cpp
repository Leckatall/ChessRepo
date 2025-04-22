// //
// // Created by Lecka on 09/03/2025.
// //
//
// #include <QGridLayout>
//
// #include "infoFrame.h"
// #include "controllers/explorercontroller.h"
//
// InfoFrame::InfoFrame(QWidget *parent)
// : QFrame(parent),
// contentsSelect(new QComboBox(this)),
// contentFrame(new QFrame(this)){
//     setFrameStyle(StyledPanel);
//     initUI();
// }
//
// void InfoFrame::setContents(const QString& content) {
//     contentFrame->setVisible(false);
//     controller = m_content_list[content];
//     controller->update_model();
//     contentFrame = controller->view();
//     contentFrame->setVisible(true);
// }
//
// void InfoFrame::initUI() {
//     // MAYBE: contentsSelect->addItems(m_content_list.keys());??
//     for(const auto& content_name: m_content_list.keys()) {
//         contentsSelect->addItem(content_name);
//     }
//     contentFrame = new QFrame(this);
//     connect(contentsSelect, QComboBox::currentTextChanged, this, setContents);
//
//     initLayout();
// }
//
// void InfoFrame::initLayout() {
//     auto *layout = new QGridLayout(this);
//     layout->addWidget(contentsSelect, 0, 0);
//     layout->addWidget(contentFrame, 1, 0);
//     for(auto* content: m_content_list) {
//         layout->addWidget(content->view(), 1, 0);
//         content->view()->setVisible(false);
//     }
//
//     this->setLayout(layout);
// }
