#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include "individual.hpp"

static const int POPULATION_SIZE = 50;
static const int TOURNAMENT_SIZE = 5;
static const double MUTATION_P = 0.02;
static const double CROSSOVER_P = 0.5;
static const double INIT_P = 0.5;
static const int MAX_GENERATIONS = 50;
static const int MAX_SAME_GENERATIONS = 5;

class Evolution{
private:
    Individual** population;
    int generation;
    const Knapsack* knapsack;

    const Individual* pickRandom() const;
    const Individual* pickBest() const;

    void selection();
    void reproduction();
    void mutation();
    const Individual* evaluation();
    bool termination() const;

    void clearPopulation();
public:
    Evolution(const Knapsack* knapsack);
    ~Evolution();
    void run();

    //TODO: print
};

#endif /* EVOLUTION_HPP */
