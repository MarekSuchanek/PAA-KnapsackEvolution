#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <iostream>

class Knapsack {
private:
    int id;
    int length;
    int capacity;
    int* prices;
    int* weights;

public:
    Knapsack();
    Knapsack(int id, int length, int capacity);
    Knapsack(const Knapsack& i);
    ~Knapsack();

    int getID() const;
    int getLength() const;
    int getCapacity() const;
    int getPrice(int i) const;
    int getWeight(int i) const;

    void setPrice(int i, int price);
    void setWeight(int i, int weight);

    int sumPrices() const;
    int sumWeights() const;

    int maxPrice() const;

    Knapsack& operator = (const Knapsack& i);

    friend std::istream& operator >> (std::istream& is, Knapsack& k);
    friend std::ostream& operator << (std::ostream& os, const Knapsack& k);
};

#endif /* KNAPSACK_HPP */
