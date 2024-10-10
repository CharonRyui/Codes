#ifndef MONSTERGENERATOR_HPP
#define MONSTERGENERATOR_HPP

#include "Monster.hpp"
class MonsterGenerator {
public:
    static std::string_view getName(int);
    static std::string_view getRoar(int);
    static Monster generate();
};

#endif