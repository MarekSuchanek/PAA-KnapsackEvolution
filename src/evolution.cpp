#include "evolution.hpp"
#include <ctime>
#include <cstdlib>

#include "random.hpp"

void Evolution::selection(){
    //TODO: tournament
}

void Evolution::reproduction(){
    //TODO: crossover
}

void Evolution::mutation(){
    for(int i = 0; i < POPULATION_SIZE; i++){
        if(Random::randProbability() < MUTATION_P){
            population[i]->mutate();
        }
    }
}

bool Evolution::termination(){
    return generation > MAX_GENERATIONS; //TODO: check convergency
}

Evolution::Evolution(const Knapsack* knapsack):knapsack(knapsack){
    population = new Individual*[POPULATION_SIZE];
    for(int i = 0; i < POPULATION_SIZE; i++){
        population[i] = new Individual(INIT_P, knapsack);
    }
    generation = 0;
}

Evolution::~Evolution(){
    for(int i = 0; i < POPULATION_SIZE; i++){
        delete population[i];
    }
    delete[] population;
}

void Evolution::run(){
    while(!termination()){
        generation++;
        selection();
        reproduction();
        mutation();
    }
}
