#include "MonsterGenerator.hpp"
#include <random>

std::string_view MonsterGenerator::getName(int n) {
    switch (n) {
        case 0:  return "Blarg";
        case 1:  return "Moog";
        case 2:  return "Pksh";
        case 3:  return "Tyrn";
        case 4:  return "Mort";
        case 5:  return "Hans";
        default: return "???";
    }
}

std::string_view MonsterGenerator::getRoar(int n) {
    switch (n) {
        case 0:  return "*ROAR*";
        case 1:  return "*peep*";
        case 2:  return "*squeal*";
        case 3:  return "*whine*";
        case 4:  return "*growl*";
        case 5:  return "*burp*";
        default: return "???";
    }
}

Monster MonsterGenerator::generate() {
    return Monster{
            static_cast<Monster::Type>(rand() % (Monster::Type::maxMonsterTypes)),
            getName(rand() % 6),
            getRoar(rand() % 6),
            rand() % 100 + 1
    };
}