//
// Created by Lecka on 24/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_SELECTION_VIEWMODEL_H
#define CHESSREPO_REPERTOIRE_SELECTION_VIEWMODEL_H
#include <QObject>

#include "persistence/repertoire_persistence.h"
#include "persistence/repertoire_service.h"

namespace Presentation::Features::Persistence {
    class RepertoireSelectionViewmodel : public QObject {
        Q_OBJECT

    public:
        explicit RepertoireSelectionViewmodel(RepertoireService &persistence,
                                              QObject *parent = nullptr);

    public slots:
        [[nodiscard]] QStringList loadRepertoireList() const;

        [[nodiscard]] Domain::Types::Repertoire::RepertoireData getRepertoireData(const QString &rep_name) const;
        void selectRepertoire(const QString &rep_name) {m_service.load_repertoire(rep_name);}

        [[nodiscard]] QString getSelectedRepertoireName() const {return m_service.get_current_repertoire().header.name;}

        [[nodiscard]] bool deleteRepertoire(const QString &rep_name) const;

        void saveRepertoire(Domain::Types::Repertoire::RepertoireData repertoire) const;

    private:
        void initConnections();

        RepertoireService &m_service;
    };
}


#endif //CHESSREPO_REPERTOIRE_SELECTION_VIEWMODEL_H
