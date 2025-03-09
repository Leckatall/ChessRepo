//
// Created by Lecka on 09/03/2025.
//

#ifndef MOVEMODEL_H
#define MOVEMODEL_H
#include <QString>


class MoveModel {
public:
    MoveModel();

private:
    QString uci;
    QString san;
    int white_wins;
    int black_wins;
    int draws;
    int move_num;
    QString opening_name;
    QString opening_eco;
};



#endif //MOVEMODEL_H
