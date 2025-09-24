//
// Created by Lecka on 21/09/2025.
//

#ifndef CHESSREPO_REPERTOIRE_VIEWMODEL_H
#define CHESSREPO_REPERTOIRE_VIEWMODEL_H
#include <QObject>

#include "repertoire/repertoire.h"
#include "types/collections.h"

namespace Infrastructure::Features::Repertoire {
    class RepertoirePersistence;
}

namespace Presentation::Features::Repertoire {
    class RepertoireViewModel : public QObject {
        Q_OBJECT

    public:
        explicit RepertoireViewModel(Domain::Types::Repertoire::RepertoireData& repertoire, QObject *parent = nullptr);

        [[nodiscard]] Domain::Types::Repertoire::RepertoireData getRepertoire() const { return m_repertoire; }

    public slots:
        bool addNextMove(const Domain::Types::MoveData &move);

        bool removeMove(const Domain::Types::MoveData &move);

        void onPositionChanged(const Domain::Types::FEN &fen);

        void setRepertoire(const Domain::Types::Repertoire::RepertoireData &repertoire);

        void setFen(const Domain::Types::FEN &fen) { onPositionChanged(fen); }

    signals:
        void moveListChanged(QList<Domain::Types::MoveData> moves);

        void saveRepertoire(Domain::Types::Repertoire::RepertoireData repertoire);

        void moveClicked(Domain::Types::UCIMove move);

    private:
        Domain::Types::Repertoire::RepertoireData& m_repertoire;
        Domain::Types::FEN m_currentFEN{Domain::Types::FEN::startingPosition()};
    };
}

#endif //CHESSREPO_REPERTOIRE_VIEWMODEL_H
