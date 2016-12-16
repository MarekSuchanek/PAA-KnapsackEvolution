#include "individual.hpp"
#include "random.hpp"


Individual::Individual(const Knapsack* k):knapsack(k), chromosome(k->getLength()){
    price = weight = 0;
    for(std::vector<bool>::size_type i = 0; i < chromosome.size(); i++)
        chromosome[i] = false;
}

Individual::Individual(bool init, const Knapsack* k):knapsack(k), chromosome(k->getLength()){
    price = weight = 0;
    for(std::vector<bool>::size_type i = 0; i < chromosome.size(); i++)
        set(i, init);
}

Individual::Individual(double probability, const Knapsack* k):knapsack(k), chromosome(k->getLength()){
    price = weight = 0;
    srand(time(NULL));
    for(std::vector<bool>::size_type i = 0; i < chromosome.size(); i++){
        set(i, Random::randProbability() > probability);
    }
}
Individual::Individual(const Individual& other):knapsack(other.knapsack), chromosome(other.chromosome){
    price = other.price;
    weight = other.weight;
}

int Individual::size() const{
    return chromosome.size();
}
bool Individual::get(int i) const{
    return chromosome[i];
}
void Individual::set(int i, bool value){
    if(chromosome[i] == value) return;
    if(chromosome[i]){
        weight -= knapsack->getWeight(i);
        price -= knapsack->getPrice(i);
    }else{
        weight += knapsack->getWeight(i);
        price += knapsack->getPrice(i);
    }
    chromosome[i] = value;
}
void Individual::neg(int i){
    set(i, !chromosome[i]);
}

int Individual::getFitness() const{
    return price;
}
int Individual::getPrice() const{
    return price;
}
int Individual::getWeight() const{
    return weight;
}


bool Individual::broken() const{
    return weight > knapsack->getCapacity();
}
void Individual::repair(){
    while(broken()){
        int point = Random::randInt(size());
        while(!get(point % size())){
            point++;
        }
        set(point % size(), false);
    }
}

bool Individual::operator < (const Individual& other) const{
    return price < other.price;
}
bool Individual::operator == (const Individual& other) const{
    return price == other.price;
}

Individual& Individual::operator = (const Individual& other){
    if(&other == this) return *this;
    knapsack = other.knapsack;
    chromosome = other.chromosome;
    price = other.price;
    weight = other.weight;
    return *this;
}
std::ostream& operator << (std::ostream& os, const Individual& ind){
    for(auto i = 0; i < ind.size(); i++) {
        os << (ind.get(i) ? '1' : '0') << ' ';
    }
    return os;
}
