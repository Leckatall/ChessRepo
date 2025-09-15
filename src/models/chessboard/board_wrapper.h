#ifndef _BOARD_WRAPPER_H
#define _BOARD_WRAPPER_H


// Stupid language needs me to tell it how to hash the easiest to hash thing in the world...
template<>
struct std::hash<chess::Square> {
    inline size_t operator ()(const chess::Square & s) const noexcept {
            return static_cast<size_t>(s.index()); // Convert to integer index
        };

};
#endif
