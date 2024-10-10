#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
    static std::mt19937 generate();
    static inline std::mt19937 mt{generate()};
public:
    static int get(int max, int min);
};

#endif