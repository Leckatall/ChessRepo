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
        explicit RepertoireSelectionViewmodel(Infrastructure::Features::Repertoire::RepertoireService &persistence,
                                              QObject *parent = nullptr);

    public slots:
        [[nodiscard]] QStringList getRepertoireList() const;

        [[nodiscard]] Domain::Types::Repertoire::RepertoireData getRepertoireData();

        void selectRepertoire(const QString &rep_name) const {
            m_service.saveLoadedRepertoire();
            m_service.loadRepertoire(rep_name);
        }

        [[nodiscard]] QString getSelectedRepertoireName() const {
            return m_service.getRepertoire()->header.name.data();
        }

        [[nodiscard]] bool deleteRepertoire(const QString &rep_name) const;

        void saveRepertoire() const;
        void editRepertoireHeader(const Domain::Types::Repertoire::Header &new_header) const;
        void createNewRepertoire(const Domain::Types::Repertoire::Header &new_header) const;

    private:
        void initConnections();

        Infrastructure::Features::Repertoire::RepertoireService &m_service;
    };
}


#endif //CHESSREPO_REPERTOIRE_SELECTION_VIEWMODEL_H
