//
// Created by Lecka on 18/09/2025.
//

#ifndef CHESSREPO_EXPLORER_VIEWMODEL_H
#define CHESSREPO_EXPLORER_VIEWMODEL_H
#include <QList>
#include <QObject>
#include <QString>
#include <qtypes.h>

#include "infrastructure/explorer/lichess_explorer_service.h"
#include "infrastructure/persistence/repertoire_persistence.h"
#include "presentation/models/explorer_tblmodel.h"

namespace Presentation::Features::Explorer {
    class ExplorerViewModel : public QObject {
        Q_OBJECT

        Q_PROPERTY(TableModel* tableModel READ tableModel CONSTANT)
        Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
        Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)
        Q_PROPERTY(QString positionSummary READ positionSummary NOTIFY positionSummaryChanged)
        Q_PROPERTY(QString fen READ fen WRITE setFen NOTIFY fenChanged)

    public:
        explicit ExplorerViewModel(Infrastructure::Features::Explorer::LichessExplorerService &service,
                                   Infrastructure::Features::Repertoire::RepertoirePersistence &persistence,
                                   QObject *parent = nullptr);

        TableModel *tableModel() { return &m_tableModel; }

        [[nodiscard]] bool loading() const { return m_loading; }
        [[nodiscard]] const QString &errorMessage() const { return m_errorMessage; }
        [[nodiscard]] const QString &positionSummary() const { return m_positionSummary; }

        [[nodiscard]] const QString &fen() const { return m_fen; }

        void setFen(const QString &fen);

    public slots:
        // Commands the view can trigger
        void exploreCurrentFen();

        void refresh();

        void indexClicked(const QModelIndex &index);

    signals:
        void moveClicked(Domain::Types::UCIMove uci);

        // Property change signals
        void loadingChanged();

        void errorMessageChanged();

        void positionSummaryChanged();

        void fenChanged(Domain::Types::FEN fen);

    private slots:
        // Connected to the service
        void onGotPositionData(const Domain::Types::PositionGraph &position);

        void onNetworkError(const QString &message);

    private:
        void initConnections();

        void setLoading(bool v);

        void setErrorMessage(const QString &m);

        void updatePositionSummary(const Domain::Types::PositionStats &position);

        Infrastructure::Features::Explorer::LichessExplorerService &m_service;
        Infrastructure::Features::Repertoire::RepertoirePersistence &m_persistence;
        TableModel m_tableModel;

        QString m_fen;
        bool m_loading{false};
        QString m_errorMessage;
        QString m_positionSummary;
    };
};


#endif //CHESSREPO_EXPLORER_VIEWMODEL_H
