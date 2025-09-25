//
// Created by Lecka on 06/04/2025.
//

#include "repertoire_service.h"
#include <QDebug>


namespace Infrastructure::Features::Repertoire {
    void RepertoireService::initConnections() {
        connect(&m_persistence, &RepertoirePersistence::repertoireListChanged,
                this, &RepertoireService::onRepertoireListChanged);
    }

    void RepertoireService::saveLoadedRepertoire() const {
        m_persistence.save_repertoire(m_current_repertoire, true);
    }

    void RepertoireService::loadRepertoire(const QString &name) {
        m_current_repertoire = m_persistence.get_repertoire(name.toStdString());
        emit repertoireLoaded();
    }

    void RepertoireService::editHeader(Domain::Types::Repertoire::Header new_header) {
        if (m_current_repertoire.header.name != new_header.name) {
            qDebug() << "Cannot change header name";
            return;
        }
        m_current_repertoire.header = new_header;
        saveLoadedRepertoire();
    }

    void RepertoireService::createRepertoire(Domain::Types::Repertoire::Header new_rep_header) const {
        m_persistence.save_repertoire({
                                          new_rep_header,
                                          Domain::Types::PositionGraph(
                                              Domain::Types::PositionKey(Domain::Types::FEN::startingPosition()),
                                              {})
                                      },
                                      false);
    }

    void RepertoireService::onRepertoireListChanged() {
        m_repertoire_title_list.clear();
        for (const auto &rep_name: m_persistence.get_repertoire_list()) {
            m_repertoire_title_list.append(QString::fromStdString(rep_name));
        }
        emit repertoireListChanged();
    }
}
