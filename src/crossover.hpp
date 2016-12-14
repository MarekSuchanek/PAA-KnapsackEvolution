#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include "individual.hpp"

class CrossoverStrategy{
public:
    virtual Individual* offspringA(const Individual* parentA, const Individual* parentB) const = 0;
    virtual Individual* offspringB(const Individual* parentA, const Individual* parentB) const = 0;
    virtual void inPlace(Individual* indA, Individual* indB) const = 0;
};

class OnePointCrossover : public CrossoverStrategy{
public:
    Individual* offspringA(const Individual* parentA, const Individual* parentB) const;
    Individual* offspringB(const Individual* parentA, const Individual* parentB) const;
    void inPlace(Individual* indA, Individual* indB) const;
};

class TwoPointCrossover : public CrossoverStrategy{
public:
    Individual* offspringA(const Individual* parentA, const Individual* parentB) const;
    Individual* offspringB(const Individual* parentA, const Individual* parentB) const;
    void inPlace(Individual* indA, Individual* indB) const;
};

class UniformCrossover : public CrossoverStrategy{
public:
    Individual* offspringA(const Individual* parentA, const Individual* parentB) const;
    Individual* offspringB(const Individual* parentA, const Individual* parentB) const;
    void inPlace(Individual* indA, Individual* indB) const;
};

#endif /* CROSSOVER_HPP */
