#ifndef MODELS_REPERTOIRE_H
#define MODELS_REPERTOIRE_H


namespace Models { class FEN; } 
namespace Models { struct Position; } 
namespace Models { struct Move; } 

namespace Models {

struct RepertoireInfo {
    QString name;

    bool forWhite {true};

    QString description;

    QString author;

    QDateTime createdAt;

    inline RepertoireInfo(QString name_, const bool forWhite_, QString description_ = "", QString author_ = "") : name(std::move(name_)),
                  forWhite(forWhite_),
                  description(std::move(description_)),
                  author(std::move(author_)),
                  createdAt(QDateTime::currentDateTime()) {
            };

    inline RepertoireInfo() : name("") {
            };

    inline bool isEmpty() const { return name.isEmpty(); };

};
class RepertoireMoves {
  public:
    QMap<FEN,Position> positions {};

    void addMove(const FEN & fromPosition, const Move & move, const FEN & toPosition, const QString & comment = QString());

    Move getRecommendedMove(const FEN & position) const;

    inline bool operator ==(const RepertoireMoves & other) const {
                return positions == other.positions;
            };

};
struct Repertoire {
    RepertoireInfo header;

    RepertoireMoves move_db;

    inline bool operator ==(const Repertoire & other) const {
                if (this->header.name != other.header.name) {
                    return false;
                }
                if (this->header.forWhite != other.header.forWhite) {
                    return false;
                }
                if (this->header.description != other.header.description) {
                    return false;
                }
                if (this->header.author != other.header.author) {
                    return false;
                }
                if (this->header.createdAt != other.header.createdAt) {
                    return false;
                }
                if (this->move_db != other.move_db) {
                    return false;
                }
                return true;
            };

};

} // namespace Models
#endif
