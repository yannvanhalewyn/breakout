#include <random>
#include "random.h"

int get_rand(int lowest, int highest) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lowest, highest);
    return dis(gen);
}
