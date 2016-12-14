#include "crossover.hpp"

#include "random.hpp"

Individual* OnePointCrossover::offspringA(const Individual* parentA, const Individual* parentB) const{
    Individual* offspring = new Individual(*parentB);
    int point = Random::randInt(offspring->size());
    for(int i = 0; i < point; i++){
        offspring->set(i, parentA->get(i));
    }
    return offspring;
}

Individual* OnePointCrossover::offspringB(const Individual* parentA, const Individual* parentB) const{
    Individual* offspring = new Individual(*parentA);
    int point = Random::randInt(offspring->size());
    for(int i = 0; i < point; i++){
        offspring->set(i, parentB->get(i));
    }
    return offspring;
}

void OnePointCrossover::inPlace(Individual* indA, Individual* indB) const{
    int point = Random::randInt(indA->size());
    bool tmp;
    for(int i = 0; i < point; i++){
        tmp = indA->get(i);
        indA->set(i, indB->get(i));
        indB->set(i, tmp);
    }
}


Individual* TwoPointCrossover::offspringA(const Individual* parentA, const Individual* parentB) const{
    Individual* offspring = new Individual(*parentA);
    int pointA = Random::randInt(offspring->size());
    int pointB = Random::randInt(offspring->size(), pointA);
    for(int i = pointA; i < pointB; i++){
        offspring->set(i, parentB->get(i));
    }
    return offspring;
}

Individual* TwoPointCrossover::offspringB(const Individual* parentA, const Individual* parentB) const{
    Individual* offspring = new Individual(*parentB);
    int pointA = Random::randInt(offspring->size());
    int pointB = Random::randInt(offspring->size(), pointA);
    for(int i = pointA; i < pointB; i++){
        offspring->set(i, parentA->get(i));
    }
    return offspring;
}

void TwoPointCrossover::inPlace(Individual* indA, Individual* indB) const{
    int pointA = Random::randInt(indA->size());
    int pointB = Random::randInt(indA->size(), pointA);
    bool tmp;
    for(int i = pointA; i < pointB; i++){
        tmp = indA->get(i);
        indA->set(i, indB->get(i));
        indB->set(i, tmp);
    }
}


Individual* UniformCrossover::offspringA(const Individual* parentA, const Individual* parentB) const{
    Individual* offspring = new Individual(*parentA);
    for(int i = 0; i < offspring->size(); i++){
        if(Random::randInt(2)){ // 50%
            offspring->set(i, parentB->get(i));
        }
    }
    return offspring;
}

Individual* UniformCrossover::offspringB(const Individual* parentA, const Individual* parentB) const{
    Individual* offspring = new Individual(*parentB);
    for(int i = 0; i < offspring->size(); i++){
        if(Random::randInt(2)){ // 50%
            offspring->set(i, parentA->get(i));
        }
    }
    return offspring;
}

void UniformCrossover::inPlace(Individual* indA, Individual* indB) const{
    bool tmp;
    for(int i = 0; i < indA->size(); i++){
        if(Random::randInt(2)){ // 50%
            tmp = indA->get(i);
            indA->set(i, indB->get(i));
            indB->set(i, tmp);
        }
    }
}
