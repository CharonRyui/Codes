#ifndef MONSTER_HPP
#define MONSTER_HPP
#include <string>
#include <string_view>

class Monster {
public:
    enum Type {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        maxMonsterTypes,
    };

    Monster(Type t, std::string_view n, std::string_view r, int h);
    constexpr std::string_view getType() const;
    void print() const;
    
private:
    Type type{};
    std::string name{"???"};
    std::string roar{"???"};
    int hitPoints{};
};

#endif