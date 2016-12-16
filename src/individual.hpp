#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <iostream>
#include <vector>

#include "knapsack.hpp"

class Individual{
private:
    const Knapsack* knapsack;
    std::vector<bool> chromosome;
    int price;
    int weight;
public:
    Individual(const Knapsack* k);
    Individual(bool init, const Knapsack* k);
    Individual(double probability, const Knapsack* k);
    Individual(const Individual& other);

    int size() const;
    bool get(int i) const;
    void set(int i, bool value);
    void neg(int i);

    int getFitness() const;
    int getPrice() const;
    int getWeight() const;

    bool broken() const;
    void repair();

    bool operator < (const Individual& other) const;
    bool operator == (const Individual& other) const;

    Individual& operator = (const Individual& other);
    friend std::ostream& operator << (std::ostream& os, const Individual& ind);
};

#endif /* INDIVIDUAL_HPP */
