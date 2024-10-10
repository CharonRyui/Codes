#include "Monster.hpp"
#include <iostream>

Monster::Monster(Type t, std::string_view n, std::string_view r, int h)
    : type{t}
    , name{n}
    , roar{r}
    , hitPoints{h} {
}

constexpr std::string_view Monster::getType() const{  	
    switch (type)
    {
    case dragon:   return "dragon";
    case goblin:   return "goblin";
    case ogre:     return "ogre";
    case orc:      return "orc";
    case skeleton: return "skeleton";
    case troll:    return "troll";
    case vampire:  return "vampire";
    case zombie:   return "zombie";
    default:       return "???";
    }

}

void Monster::print() const {
    std::cout << name << " the " << getType();

    if (hitPoints <= 0)
        std::cout << " is dead.\n";
    else
        std::cout << " has " << hitPoints << " hit points and says " << roar << ".\n";
}