//
// Created by Lecka on 15/06/2025.
//

#ifndef REPERTOIRE_VIEWER_CONTROLLER_H
#define REPERTOIRE_VIEWER_CONTROLLER_H
#include <QObject>

#include "services/repertoire_service.h"
#include "ui/components/repertoire_viewer/repertoire_view.h"


namespace repertoire_viewer {
    class Controller : public QObject {
        Q_OBJECT

    public:
        explicit Controller(RepertoireService &service, QObject *parent = nullptr);

        [[nodiscard]] View *view() const { return m_view; }

    public slots:
        void getUciMovesForFEN(const Models::FEN& fen);

        void showMoves(const QList<Models::Move> &moves) const;

    signals:
        void moveClicked(Models::UCIMove uci);

        void requestMoveModels(QList<Models::UCIMove> uci_moves);

    private:
        void initConnections();

        RepertoireService &m_rep_service;
        View *m_view;
    };
}


#endif //REPERTOIRE_VIEWER_CONTROLLER_H
