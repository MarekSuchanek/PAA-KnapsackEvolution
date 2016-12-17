#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include <iostream>

#include "individual.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

struct EvolutionConfig{
    int populationSize;
    int tournamentSize;
    double pMutation;
    double pCrossover;
    double pInit;
    int maxGenerations;
    int maxSameGenerations;

    const CrossoverStrategy* cs;
    const MutationStrategy* ms;

    EvolutionConfig();
    ~EvolutionConfig();

    void loadArgs(int argc, char const *argv[]);

    const CrossoverStrategy* getCrossoverStrategy() const;
    const MutationStrategy* getMutationStrategy() const;

    void print(std::ostream& os) const;
    friend std::ostream& operator << (std::ostream& os, const EvolutionConfig& cfg);
};

class Evolution{
private:
    const Knapsack* knapsack;
    const EvolutionConfig& cfg;

    Individual** population;

    int generation;
    int sameBest;
    Individual* bestIndividual;
    Individual* worstIndividual;
    double averageFitness;

    const CrossoverStrategy* cs;
    const MutationStrategy* ms;

    const Individual* pickRandom() const;
    const Individual* pickBest() const;

    void selection();
    void reproduction();
    void mutation();
    void evaluation();
    bool termination() const;

    void clearPopulation();
public:
    Evolution(const Knapsack* knapsack, const EvolutionConfig& cfg);
    ~Evolution();

    bool isTerminated() const;
    int getGeneration() const;
    int getBestFitness() const;
    int getWorstFitness() const;
    double getAvgFitness() const;
    const Individual* getBest() const;
    const Individual* getWorst() const;

    void run();
    void run(std::ostream& os);
    void step();

    void print(std::ostream& os) const;

    friend std::ostream& operator << (std::ostream& os, const Evolution& evo);
};

#endif /* EVOLUTION_HPP */
