//
// Created by Lecka on 17/09/2025.
//

#include "lichess_request_builder.h"

#include <QUrlQuery>

using namespace Infrastructure::Features::Explorer;
QUrl LichessRequestBuilder::buildApiUrl(const Domain::Types::FEN &fen) const {
    QUrl url(QString::fromStdString(LICHESS_URL));
    QUrlQuery query;

    if (!fen.empty()) {
        query.addQueryItem("fen", QString::fromStdString(fen));
    }

    // Add configuration parameters
    for (auto [key, value]: config.toMap()) {
        if (!value.empty()) {
            query.addQueryItem(QString::fromStdString(key), QString::fromStdString(value));
        }
    }

    url.setQuery(query);
    return url;
}
