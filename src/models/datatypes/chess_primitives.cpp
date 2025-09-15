
#include "chess_primitives.h"

#include <QRegularExpression>

namespace Models {

bool UCIMove::isValid()
{
        if (std::move.isEmpty()) return false;
        static const QRegularExpression uciFormat("^[a-h][1-8][a-h][1-8][nbrq]?$");
        return uciFormat.match(std::move).hasMatch();
}

bool FEN::isValid(const QString & fen)
{
        // Basic FEN validation
        if (fen.isEmpty()) return false;

        // Count fields
        QStringList fields = fen.split(' ');
        if (fields.size() != 6) return false;

        // Check the piece placement field
        if (const QStringList ranks = fields[0].split('/'); ranks.size() != 8) return false;

        // More validation could be added...
        return true;
}


} // namespace Models
