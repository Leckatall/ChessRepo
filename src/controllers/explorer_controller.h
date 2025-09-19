//
// Created by Lecka on 09/03/2025.
//

#ifndef EXPLORERCONTROLLER_H
#define EXPLORERCONTROLLER_H
#include <QGridLayout>
#include <QObject>
#include <QStringList>
#include <QLabel>

#include "../presentation/models/explorer_tblmodel.h"
#include "../infrastructure/explorer/lichess_explorer_service.h"
#include "presentation/models/tablemodel.h"
#include "ui/components/explorer/explorer_view.h"

namespace application {
    class Application;
}

namespace explorer {
    // DEPRECATED: Use Presentation::Features::Explorer::ExplorerViewModel instead
    class Controller : public QObject {
        Q_OBJECT
        // TODO: Add engine support
        // TODO: Add integration with openerController and highlight prepped moves
    public:
        explicit Controller(Infrastructure::Features::Explorer::LichessExplorerService &service, QObject *parent = nullptr);

        [[nodiscard]] View *view() const { return m_view; }

    public slots:
        void exploreFen(const QString &fen);

        void updatePositionData(const Models::PositionData &position);

    signals:
        void moveClicked(Domain::Types::UCIMove uci);

    private:
        void initConnections();

        Infrastructure::Features::Explorer::LichessExplorerService &m_lichess_api;
        Models::PositionData m_current_position{};
        Presentation::Features::Explorer::ExplorerViewModel m_explorerViewModel;
        View *m_view;
    };
}


#endif //EXPLORERCONTROLLER_H
