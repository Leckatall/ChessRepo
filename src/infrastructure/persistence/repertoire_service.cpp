//
// Created by Lecka on 06/04/2025.
//

#include "repertoire_service.h"


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

    void RepertoireService::onRepertoireListChanged() {
        m_repertoire_title_list.clear();
        for (const auto &rep_name: m_persistence.get_repertoire_list()) {
            m_repertoire_title_list.append(QString::fromStdString(rep_name));
        }
        emit repertoireListChanged();
    }
}
