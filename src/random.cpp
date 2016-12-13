#include "random.hpp"

#include <ctime>
#include <cstdlib>

Random::Random(){
    srand(time(NULL));
}

Random& Random::getInstance(){
    static Random instance;
    return instance;
}

int Random::randInt(int maxValue, int minValue){
    return getInstance().getRandInt(maxValue, minValue);
}

int Random::randInt(int maxValue){
    return getInstance().getRandInt(maxValue);
}

double Random::randProbability(){
    return getInstance().getRandProbability();
}

int Random::getRandInt(int maxValue, int minValue){
    return rand() % (maxValue - minValue) + minValue;
}

int Random::getRandInt(int maxValue){
    return rand() % maxValue;
}

double Random::getRandProbability(){
    return (double)rand() / (double)RAND_MAX
}
