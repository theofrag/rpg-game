#include "Randomness.h"

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_int_distribution<int> dist(1, 100);

bool avoid_attack_prob(int prob){
    if(prob < 0)
        return 0;
    return (dist(rd) < prob);
}

bool decide_battle(){
    return (dist(rd) < 11);
}

int getIntFromRange(int from, int to){
    std::uniform_int_distribution<int> distr(from, to);
    return distr(mt);
}