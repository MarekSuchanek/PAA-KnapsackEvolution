#include "knapsack.hpp"

Knapsack::Knapsack() {
    id = length = capacity = 0;
    prices = weights = NULL;
}

Knapsack::Knapsack(int id, int length, int capacity):id(id),length(length),capacity(capacity) {
    prices = weights = NULL;
}

Knapsack::Knapsack(const Knapsack& i):id(i.id),length(i.length),capacity(i.capacity) {
    prices = new int[length];
    weights = new int[length];
    for (int x = 0; x < i.length; x++) {
        prices[x] = i.prices[x];
        weights[x] = i.weights[x];
    }
}

Knapsack::~Knapsack() {
    delete[] prices;
    delete[] weights;
}

int Knapsack::getID() const {
    return id;
}

int Knapsack::getLength() const {
    return length;
}

int Knapsack::getCapacity() const {
    return capacity;
}

int Knapsack::getPrice(int i) const {
    return prices[i];
}

int Knapsack::getWeight(int i) const {
    return weights[i];
}

void Knapsack::setPrice(int i, int price) {
    prices[i] = price;
}

void Knapsack::setWeight(int i, int weight) {
    weights[i] = weight;
}

int Knapsack::sumPrices() const {
    int s = 0;
    for (int i = 0; i < length; i++) {
        s += prices[i];
    }
    return s;
}

int Knapsack::sumWeights() const {
    int s = 0;
    for (int i = 0; i < length; i++) {
        s += weights[i];
    }
    return s;
}

int Knapsack::maxPrice() const {
    int maxPrice = 0;
    for(int x = 0; x < length; x++) {
        if(maxPrice < prices[x]) {
            maxPrice = prices[x];
        }
    }
    return maxPrice;
}

Knapsack& Knapsack::operator = (const Knapsack& i) {
    if(this == &i) return *this;
    delete[] prices;
    delete[] weights;

    id = i.id;
    length = i.length;
    capacity = i.capacity;
    prices = new int[length];
    weights = new int[length];
    for (int x = 0; x < i.length; x++) {
        prices[x] = i.prices[x];
        weights[x] = i.weights[x];
    }
    return *this;
}

std::istream& operator >> (std::istream& is, Knapsack& k) {
    delete[] k.prices;
    delete[] k.weights;
    is >> k.id >> k.length >> k.capacity;
    k.prices = new int[k.length];
    k.weights = new int[k.length];
    for (int i = 0; i < k.length; i++) {
        is >> k.weights[i] >> k.prices[i];
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Knapsack& k) {
    os << k.id << " " << k.length << " " << k.capacity;
    for (int i = 0; i < k.length; i++) {
        os << " " << k.weights[i] << " " << k.prices[i];
    }
    return os;
}
