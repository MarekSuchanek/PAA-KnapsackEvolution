#include <iostream>
#include "knapsack.hpp"
#include "evolution.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

using namespace std;



int main(int argc, char const *argv[]) {
    Knapsack k;
    cin >> k;
    OnePointCrossover crossover;
    FlipBitMutation mutation;
    Evolution e(&k, &crossover, &mutation);
    e.run();
    return 0;
}
