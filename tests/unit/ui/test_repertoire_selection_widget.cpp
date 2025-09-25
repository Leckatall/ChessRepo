//
// Created by Lecka on 25/09/2025.
//

#include <QtTest/QtTest>

#include "compound_widgets/repertoire_selection_widget.h"


class TestRepertoireSelectionWidget : public QObject {
    Q_OBJECT

private:
    Domain::Types::Repertoire::RepertoireData testRepertoireData;
    QTemporaryDir *temp_dir;
    Infrastructure::Features::Repertoire::RepertoirePersistence* m_repertoirePersistence;
    Infrastructure::Features::Repertoire::RepertoireService *m_repertoireService;
    Presentation::Features::Persistence::RepertoireSelectionViewmodel* m_viewmodel;
    View::Features::Persistence::RepertoireSelectionWidget *m_widget;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testLoadRepertoireList();


};
