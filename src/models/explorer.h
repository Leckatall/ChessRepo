//
// Created by Lecka on 04/03/2025.
//

#ifndef EXPLORER_H
#define EXPLORER_H
#include <chess.hpp>

class Explorer {
public:
    chess::Movelist getMoves(std::string FEN);
};



#endif //EXPLORER_H
