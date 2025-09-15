#ifndef _OPENINGBOOK_H
#define _OPENINGBOOK_H


struct Move {
    QString move;

    QString resultHash;

};
struct BoardState {
    QString comment;

    QList<Move> moves;

};
typedef QObject typedef31;
class OpeningBook : public typedef31 {
  Q_OBJECT
  public:
    bool save(QString filepath);

    QString forColor;

    QString title;

    QString description;

    QHash<QString,BoardState> states;

};
#endif
