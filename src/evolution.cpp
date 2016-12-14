#include "evolution.hpp"
#include <ctime>
#include <cstdlib>

#include "random.hpp"

const Individual* Evolution::pickRandom() const{
    return population[Random::randInt(POPULATION_SIZE, 0)];
}

const Individual* Evolution::pickBest() const{
    int best = 0;
    for(int i = 1; i < POPULATION_SIZE; i++){
        if(population[i]->getFitness() > population[best]->getFitness()){
            best = i;
        }
    }
    return population[best];
}

void Evolution::selection(){
    Individual** nextPopulation = new Individual*[POPULATION_SIZE];
    for(int i = 0; i < POPULATION_SIZE; i++){
        const Individual* winner = pickRandom();
        for(int j = 1; j < TOURNAMENT_SIZE; j++){
            const Individual* challenger = pickRandom();
            if(winner->getFitness() < challenger->getFitness()){
                winner = challenger;
            }
        }
        nextPopulation[i] = new Individual(*winner);
    }
    clearPopulation();
    population = nextPopulation;
}

void Evolution::reproduction(){
    for(int i = 0; i < POPULATION_SIZE; i+=2){
        if(Random::randProbability() < CROSSOVER_P){
            cs->inPlace(population[i], population[i+1]);
        }
    }
}

void Evolution::mutation(){
    for(int i = 0; i < POPULATION_SIZE; i++){
        if(Random::randProbability() < MUTATION_P){
            ms->inPlace(population[i]);
        }
    }
}

bool Evolution::termination() const{
    return generation > MAX_GENERATIONS; //TODO: check convergency
}

const Individual* Evolution::evaluation(){
    int best = 0;
    for(int i = 0; i < POPULATION_SIZE; i++){
        population[i]->repair();
        if(population[i]->getFitness() > population[best]->getFitness()){
            best = i;
        }
    }
    return population[best];
}


void Evolution::clearPopulation(){
    for(int i = 0; i < POPULATION_SIZE; i++){
        delete population[i];
    }
    delete[] population;
    population = NULL;
}

Evolution::Evolution(const Knapsack* knapsack, const CrossoverStrategy* cs, const MutationStrategy* ms):knapsack(knapsack),cs(cs),ms(ms){
    population = new Individual*[POPULATION_SIZE];
    for(int i = 0; i < POPULATION_SIZE; i++){
        population[i] = new Individual(INIT_P, knapsack);
    }
    generation = 0;
}

Evolution::~Evolution(){
    clearPopulation();
}

void Evolution::run(){
    generation = 0;
    int sameBest = 0;
    const Individual* best = evaluation();
    const Individual* newBest = NULL;

    while(!termination()){
        generation++;
        selection();
        reproduction();
        mutation();
        newBest = evaluation();

        if(newBest->getFitness() == best->getFitness()){
            sameBest++;
        }else{
            sameBest = 0;
        }
        best = newBest;
        std::cout << generation << ": " << best->getFitness() << std::endl;
    }
}
