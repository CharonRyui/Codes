#include "Random.h"
#include <chrono>
std::mt19937 Random::generate() {
    std::random_device rd{};
    std::seed_seq ss{
        static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
            rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    return std::mt19937{ss}; 
}

int Random::get(int min, int max) {
        return std::uniform_int_distribution<>{min, max}(mt);
}