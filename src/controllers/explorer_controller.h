//
// Created by Lecka on 09/03/2025.
//

#ifndef EXPLORERCONTROLLER_H
#define EXPLORERCONTROLLER_H
#include <QGridLayout>
#include <QObject>
#include <QStringList>
#include <QLabel>

#include "models/explorer_tblmodel.h"
#include "services/LichessService.h"
#include "ui/components/explorer/explorer_view.h"

namespace application {
    class Application;
}

namespace explorer {
    class Controller : public QObject {
        Q_OBJECT
        // TODO: Add engine support
        // TODO: Add integration with openerController and highlight prepped moves
    public:
        explicit Controller(LichessService &service, QObject *parent = nullptr);

        [[nodiscard]] View *view() const { return m_view; }

    public slots:
        void exploreFen(const QString &fen) const;

        void updateMoves(const QList<Models::MoveData> &moves);

        void updatePositionData(const Models::PositionData &position);

    signals:
        void moveClicked(Models::UCIMove uci);

    private:
        void initConnections();

        LichessService &m_lichess_api;
        Models::PositionData m_current_position{};
        TblModel m_explorerTblModel;
        View *m_view;
    };
}


#endif //EXPLORERCONTROLLER_H
