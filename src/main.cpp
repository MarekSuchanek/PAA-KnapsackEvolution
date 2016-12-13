#include <iostream>
#include "knapsack.hpp"
#include "evolution.hpp"

using namespace std;



int main(int argc, char const *argv[]) {
    Knapsack k;
    cin >> k;
    Evolution e(&k);
    e.run();
    return 0;
}
