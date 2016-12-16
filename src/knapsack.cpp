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

int Knapsack::getOptimum() const {
    return optimum;
}

void Knapsack::setPrice(int i, int price) {
    prices[i] = price;
}

void Knapsack::setWeight(int i, int weight) {
    weights[i] = weight;
}

void Knapsack::setOptimum(int opt){
    optimum = opt;
}

double Knapsack::relativeError(int apx){
    return absoluteError(apx) / (double)optimum;
}

int Knapsack::absoluteError(int apx){
    return optimum - apx;
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

void Knapsack::loadInstance(std::istream& is){
    int newLength;
    is >> id >> newLength >> capacity;
    if(is.fail()) return;
    if(newLength != length){
        delete[] prices;
        delete[] weights;
        length = newLength;
        prices = new int[length];
        weights = new int[length];
    }
    for (int i = 0; i < length; i++) {
        is >> weights[i] >> prices[i];
    }
}

void Knapsack::loadSolution(std::istream& is){
    int xid, xlen, dummy;
    is >> xid >> xlen;
    if(is.fail()) return;
    if(xid == id && xlen == length){
        is >> optimum;
    }else{
        is >> dummy;
    }
    for (int i = 0; i < length; i++) {
        is >> dummy;
    }
}

std::istream& operator >> (std::istream& is, Knapsack& k) {
    k.loadInstance(is);
    return is;
}

std::ostream& operator << (std::ostream& os, const Knapsack& k) {
    os << k.id << " " << k.length << " " << k.capacity;
    for (int i = 0; i < k.length; i++) {
        os << " " << k.weights[i] << " " << k.prices[i];
    }
    return os;
}
