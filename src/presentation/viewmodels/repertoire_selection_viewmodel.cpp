//
// Created by Lecka on 24/09/2025.
//

#include "repertoire_selection_viewmodel.h"
#include <QDebug>

namespace Presentation::Features::Persistence {
    RepertoireSelectionViewmodel::RepertoireSelectionViewmodel(
        Infrastructure::Features::Repertoire::RepertoireService &persistence, QObject *parent)
        : QObject(parent),
          m_service(persistence) {
        initConnections();
    }
    void RepertoireSelectionViewmodel::initConnections() {

    }

    QStringList RepertoireSelectionViewmodel::getRepertoireList() const {
        return m_service.getRepertoireList();
    }

    Domain::Types::Repertoire::RepertoireData RepertoireSelectionViewmodel::getRepertoireData() {
        auto* rep = m_service.getRepertoire();
        if (rep == nullptr) {
            qDebug() << "No repertoire loaded";
            return {};
        }
        return *m_service.getRepertoire();
    }


    bool RepertoireSelectionViewmodel::deleteRepertoire(const QString &rep_name) const {
        qDebug() << "Not implemented: RepertoireSelectionViewmodel::deleteRepertoire";
        return false;
    }

    void RepertoireSelectionViewmodel::saveRepertoire() const {
        m_service.saveLoadedRepertoire();
    }

    void RepertoireSelectionViewmodel::editRepertoireHeader(const Domain::Types::Repertoire::Header &new_header) const {
        m_service.editHeader(new_header);
    }


    void RepertoireSelectionViewmodel::createNewRepertoire(const Domain::Types::Repertoire::Header &new_header) const {
        m_service.createRepertoire(new_header);
    }
}
