#ifndef RANDOM_HPP
#define RANDOM_HPP

class Random{
private:
    Random();
public:
    static Random& getInstance();
    static int randInt(int maxValue, int minValue);
    static int randInt(int maxValue);
    static double randProbability();

    int getRandInt(int maxValue, int minValue);
    int getRandInt(int maxValue);
    double getRandProbability();
};

#endif /*RANDOM_HPP*/
