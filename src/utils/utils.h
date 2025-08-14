//
// Created by Lecka on 14/08/2025.
//

#ifndef CHESSREPO_UTILS_H
#define CHESSREPO_UTILS_H
#include <QString>

namespace Utils {
    inline QString formatPercentage(const double value, const int precision = 2) {
        return QString::number(value * 100, 'f', precision) + "%";
    }
}


#endif //CHESSREPO_UTILS_H