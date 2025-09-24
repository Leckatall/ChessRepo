//
// Created by Lecka on 24/09/2025.
//

#include "repertoire_selection_viewmodel.h"
#include <QDebug>

namespace Presentation::Features::Persistence {
    RepertoireSelectionViewmodel::RepertoireSelectionViewmodel(
        RepertoireService &persistence, QObject *parent)
        : QObject(parent),
          m_service(persistence) {
        initConnections();
    }
    void RepertoireSelectionViewmodel::initConnections() {

    }

    QStringList RepertoireSelectionViewmodel::loadRepertoireList() const {
        QStringList rep_list;
        for (const auto &rep_name: m_service.get_repertoire_list()) {
            rep_list.append(QString::fromStdString(rep_name));
        }
        return rep_list;
    }

    Domain::Types::Repertoire::RepertoireData RepertoireSelectionViewmodel::getRepertoireData(
        const QString &rep_name) const {
        return m_service.get_repertoire(rep_name.toStdString());
    }

    bool RepertoireSelectionViewmodel::deleteRepertoire(const QString &rep_name) const {
        qDebug() << "Not implemented: RepertoireSelectionViewmodel::deleteRepertoire";
        return false;
    }

    void RepertoireSelectionViewmodel::saveRepertoire(Domain::Types::Repertoire::RepertoireData repertoire) const {
        m_service.save_repertoire(repertoire, true);
    }

}
